// Copyright 2019 Vilya Harvey
#include <miniply.h>
#include <happly.h>
#include <tinyply.h>
#include <rply.h>

#include <vh_cmdline.h>
#include <vh_time.h>

#include <atomic>
#include <cstdio>
#include <string>
#include <thread>


// Needed for msh_std.h
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstring>
#ifdef __APPLE__
#include <sys/stat.h>
#include <unistd.h>
#endif
#define MSH_STD_IMPLEMENTATION
#define MSH_PLY_IMPLEMENTATION
#include <msh_std.h>
#include <msh_ply.h>


//
// Constants
//

static const char* kTitle = "PLY Parsing Performance Comparison";
static const int kMajorVersion = 0;
static const int kMinorVersion = 0;

enum CmdLineOption {
  eHelp,
  eVersion,
  eNoMiniPLY,
  eNoHapply,
  eNoTinyPLY,
  eNoRPLY,
  eNoMSHPly,
  eNoPrewarm,
  eCSV,
  eQuiet,
  eOutFile,
  eTransposed,
  eSummary,
  eSpeedup,
  eSlowdown,
  ePrecognition,
};

static const vh::CommandLineOption options[] = {
  { eHelp,              'h',  "help",           nullptr, nullptr, "Print this help message and exit."                               },
  { eVersion,           'v',  "version",        nullptr, nullptr, "Print the application version and exit."                         },
  { eNoMiniPLY,         '\0', "no-miniply",     nullptr, nullptr, "Disable the \"minpbrt\" parser."                                 },
  { eNoHapply,          '\0', "no-happly",      nullptr, nullptr, "Disable the \"happly\" parser."                                  },
  { eNoTinyPLY,         '\0', "no-tinyply",     nullptr, nullptr, "Disable the \"tinyply\" parser."                                 },
  { eNoRPLY,            '\0', "no-rply",        nullptr, nullptr, "Disable the \"rply\" parser."                                    },
  { eNoMSHPly,          '\0', "no-mshply",      nullptr, nullptr, "Disable the \"msh_ply\" parser."                                 },
  { eNoPrewarm,         '\0', "no-prewarm",     nullptr, nullptr, "Don't pre-warm the disk cache before parsing (useful for very large scenes)." },
  { eCSV,               '\0', "csv",            nullptr, nullptr, "Format output as CSV, for easy import into a spreadsheet."       },
  { eQuiet,             'q',  "quiet",          nullptr, nullptr, "Don't print any intermediate text, just the final results."      },
  { eOutFile,           'o',  "out-file",       "%s",    nullptr, "Write the results to a file rather than stdout."                 },
  { eTransposed,        '\0', "transposed",     nullptr, nullptr, "Parse all files with one parser before parsing all files with the next parser." },
  { eSummary,           's',  "summary",        nullptr, nullptr, "Only show the total parsing times, not the times for each file." },
  { eSpeedup,           '\0', "speedup",        nullptr, nullptr, "Include the relative speedup of each parser in the output."      },
  { eSlowdown,          '\0', "slowdown",       nullptr, nullptr, "Include the relative slowdown of each parser in the output."     },
  { ePrecognition,      '\0', "precognition",   nullptr, nullptr, "Run a pre-pass to determine how many vertices there are per face in each input file and pass that info to the parsers." },
  { vh::kUnknownOption, '\0', nullptr,          nullptr, nullptr, nullptr                                                           }
};


namespace vh {

  // If the vertsPerFace parameter is non-zero, it means that all faces should
  // be assumed to have exactly `vertsPerFace` vertices and any parsers that can
  // take advantage of this should do so. If it's zero, it means the number of
  // vertices per face is unknown and may possibly vary from face to face.
  typedef bool (*ParserFunc)(const char* filename, uint32_t vertsPerFace, double& parsingMSOut);


  static bool prewarm_parser(const char* filename);
  static bool parse_with_miniply(const char* filename, uint32_t vertsPerFace, double& parsingMSOut);
  static bool parse_with_happly(const char* filename, uint32_t vertsPerFace, double& parsingMSOut);
  static bool parse_with_tinyply(const char* filename, uint32_t vertsPerFace, double& parsingMSOut);
  static bool parse_with_rply(const char* filename, uint32_t vertsPerFace, double& parsingMSOut);
  static bool parse_with_msh_ply(const char* filename, uint32_t vertsPerFace, double& parsingMSOut);


  enum ParserID {
    eMiniPLY,
    eHapply,
    eTinyPLY,
    eRPLY,
    eMSHPly,
  };


  static const char* kParserNames[] = {
    "miniply",
    "happly",
    "tinyply",
    "rply",
    "msh_ply",
  };


  static const ParserFunc kParsers[] = {
    parse_with_miniply,
    parse_with_happly,
    parse_with_tinyply,
    parse_with_rply,
    parse_with_msh_ply,
  };
  static const uint32_t kNumParsers = sizeof(kParsers) / sizeof(kParsers[0]);


  struct Result {
    std::string filename;
    double msecs[kNumParsers];
    bool ok[kNumParsers];
  };


  static int file_open(FILE** f, const char* filename, const char* mode)
  {
  #ifdef _WIN32
    return fopen_s(f, filename, mode);
  #else
    *f = fopen(filename, mode);
    return (*f != nullptr) ? 0 : errno;
  #endif
  }


  // This is what we populate to test & benchmark data extraction from the PLY
  // file. It's an indexed mesh which allows any number of vertices per
  // polygon (no triangulation required).
  struct PolyMesh {
    // Per-vertex data
    float* pos     = nullptr; // has 3*numVerts elements.
    float* normal  = nullptr; // if non-null, has 3 * numVerts elements.
    float* uv      = nullptr; // if non-null, has 2 * numVerts elements.
    uint32_t numVerts   = 0;

    // Per-index data
    int* indices   = nullptr;
    uint32_t numIndices = 0; // number of indices = sum of the number of indices for each face

    // Per-face data
    uint32_t* faceStart = nullptr; // Entry 'i' is the index at which the indices for this face start. It has `numFaces + 1` entries.
    uint32_t numFaces = 0;

    ~PolyMesh() {
      delete[] pos;
      delete[] normal;
      delete[] uv;
      delete[] indices;
      delete[] faceStart;
    }

    bool all_indices_valid() const {
      for (uint32_t i = 0; i < numIndices; i++) {
        if (indices[i] < 0 || uint32_t(indices[i]) >= numVerts) {
          return false;
        }
      }
      return true;
    }
  };


  // Read the PLY file so that it's in the OS's disk cache when we run the
  // parsing performance tests. We just read the file into memory without
  // doing any processing on it for these purposes.
  static bool prewarm_parser(const char* filename)
  {
    FILE* f = nullptr;
    if (file_open(&f, filename, "rb") != 0) {
      return false;
    }

    const size_t bufLen = 1024 * 1024;
    char* buffer = new char[bufLen + 1];
    buffer[bufLen] = '\0';
    while (fread(buffer, sizeof(char), bufLen, f) == bufLen) {
      continue;
    }
    fclose(f);
    delete[] buffer;

    return true;
  }


  static uint32_t verts_per_face(const char* filename)
  {
    uint32_t idx;
    miniply::PLYReader reader(filename);
    while (reader.valid() && reader.has_element()) {
      if (reader.element_is(miniply::kPLYFaceElement) && reader.load_element() && reader.find_indices(&idx)) {
        const uint32_t numFaces = reader.num_rows();
        const uint32_t* counts = reader.get_list_counts(idx);
        if (numFaces == 0 || counts == nullptr) {
          return 0;
        }
        uint32_t expectedVerts = counts[0];
        for (uint32_t i = 0; i < numFaces; i++) {
          if (counts[i] != expectedVerts) {
            return 0;
          }
        }
        return expectedVerts;
      }
      reader.next_element();
    }
    return 0;
  }


  static bool parse_with_miniply(const char* filename, uint32_t vertsPerFace, double& parsingMSOut)
  {
    Timer timer(true); // true --> autostart the timer.

    miniply::PLYReader reader(filename);
    if (!reader.valid()) {
      return false;
    }

    std::vector<uint32_t> listIdxs;
    if (vertsPerFace != 0) {
      miniply::PLYElement* facesElem = reader.get_element(reader.find_element(miniply::kPLYFaceElement));
      if (facesElem != nullptr) {
        listIdxs.resize(vertsPerFace);
        facesElem->convert_list_to_fixed_size(facesElem->find_property("vertex_indices"), vertsPerFace, listIdxs.data());
      }
    }

    PolyMesh* polymesh = new PolyMesh();
    bool gotVerts = false;
    bool gotFaces = false;
    while (reader.has_element() && (!gotVerts || !gotFaces)) {
      if (!gotVerts && reader.element_is(miniply::kPLYVertexElement)) {
        if (!reader.load_element()) {
          break;
        }
        uint32_t propIdxs[3];
        if (!reader.find_pos(propIdxs)) {
          break;
        }
        polymesh->numVerts = reader.num_rows();
        polymesh->pos = new float[polymesh->numVerts * 3];
        reader.extract_properties(propIdxs, 3, miniply::PLYPropertyType::Float, polymesh->pos);
        if (reader.find_normal(propIdxs)) {
          polymesh->normal = new float[polymesh->numVerts * 3];
          reader.extract_properties(propIdxs, 3, miniply::PLYPropertyType::Float, polymesh->normal);
        }
        if (reader.find_texcoord(propIdxs)) {
          polymesh->uv = new float[polymesh->numVerts * 2];
          reader.extract_properties(propIdxs, 2, miniply::PLYPropertyType::Float, polymesh->uv);
        }
        gotVerts = true;
      }
      else if (!gotFaces && reader.element_is(miniply::kPLYFaceElement)) {
        if (!reader.load_element()) {
          break;
        }
        if (vertsPerFace != 0) {
          polymesh->numFaces = reader.num_rows();
          polymesh->faceStart = new uint32_t[polymesh->numFaces + 1];
          for (uint32_t i = 0; i < polymesh->numFaces; i++) {
            polymesh->faceStart[i] = i * vertsPerFace;
          }

          polymesh->numIndices = polymesh->numFaces * vertsPerFace;
          polymesh->indices = new int[polymesh->numIndices];
          reader.extract_properties(listIdxs.data(), vertsPerFace, miniply::PLYPropertyType::Int, polymesh->indices);
        }
        else {
          uint32_t propIdx;
          if (!reader.find_indices(&propIdx)) {
            break;
          }

          polymesh->numFaces = reader.num_rows();
          polymesh->faceStart = new uint32_t[polymesh->numFaces + 1];
          const uint32_t* faceCounts = reader.get_list_counts(propIdx);
          uint32_t faceStart = 0;
          for (uint32_t i = 0; i < polymesh->numFaces; i++) {
            polymesh->faceStart[i] = faceStart;
            faceStart += faceCounts[i];
          }
          polymesh->faceStart[polymesh->numFaces] = faceStart;

          polymesh->numIndices = polymesh->faceStart[polymesh->numFaces];
          polymesh->indices = new int[polymesh->numIndices];
          reader.extract_list_property(propIdx, miniply::PLYPropertyType::Int, polymesh->indices);
        }

        gotFaces = true;
      }
      reader.next_element();
    }

    if (!gotVerts || !gotFaces) {
      delete polymesh;
      return false;
    }

    timer.stop();
    parsingMSOut = timer.elapsedMS();

    delete polymesh;
    return true;
  }


  static bool parse_with_happly(const char* filename, uint32_t /*vertsPerFace*/, double& parsingMSOut)
  {
    Timer timer(true); // true --> autostart the timer.

    happly::PLYData plyIn(filename);
    if (!plyIn.hasElement("vertex") || !plyIn.hasElement("face")) {
      return false;
    }

    PolyMesh* polymesh = new PolyMesh();

    // Load vertex data.
    {
      happly::Element& elem = plyIn.getElement("vertex");
      polymesh->numVerts = uint32_t(elem.count);

      polymesh->pos = new float[polymesh->numVerts * 3];
      std::vector<float> xvals = elem.getProperty<float>("x");
      std::vector<float> yvals = elem.getProperty<float>("y");
      std::vector<float> zvals = elem.getProperty<float>("z");
      for (uint32_t i = 0; i < polymesh->numVerts; i++) {
        polymesh->pos[3 * i    ] = xvals[i];
        polymesh->pos[3 * i + 1] = yvals[i];
        polymesh->pos[3 * i + 2] = zvals[i];
      }

      if (elem.hasProperty("nx") && elem.hasProperty("ny") && elem.hasProperty("nz")) {
        polymesh->normal = new float[polymesh->numVerts * 3];
        xvals = elem.getProperty<float>("nx");
        yvals = elem.getProperty<float>("ny");
        zvals = elem.getProperty<float>("nz");
        for (uint32_t i = 0; i < polymesh->numVerts; i++) {
          polymesh->normal[3 * i    ] = xvals[i];
          polymesh->normal[3 * i + 1] = yvals[i];
          polymesh->normal[3 * i + 2] = zvals[i];
        }
      }

      bool hasUV = false;
      if (elem.hasProperty("u") && elem.hasProperty("v")) {
        xvals = elem.getProperty<float>("u");
        yvals = elem.getProperty<float>("v");
        hasUV = true;
      }
      else if (elem.hasProperty("s") && elem.hasProperty("t")) {
        xvals = elem.getProperty<float>("s");
        yvals = elem.getProperty<float>("t");
        hasUV = true;
      }
      else if (elem.hasProperty("texture_u") && elem.hasProperty("texture_v")) {
        xvals = elem.getProperty<float>("texture_u");
        yvals = elem.getProperty<float>("texture_v");
        hasUV = true;
      }
      else if (elem.hasProperty("texture_s") && elem.hasProperty("texture_t")) {
        xvals = elem.getProperty<float>("texture_s");
        yvals = elem.getProperty<float>("texture_t");
        hasUV = true;
      }
      if (hasUV) {
        polymesh->uv = new float[polymesh->numVerts * 2];
        for (uint32_t i = 0; i < polymesh->numVerts; i++) {
          polymesh->uv[2 * i    ] = xvals[i];
          polymesh->uv[2 * i + 1] = yvals[i];
        }
      }
    }

    // Load index data.
    {
      std::vector<std::vector<int>> faces = plyIn.getFaceIndices<int>();

      polymesh->numFaces = static_cast<uint32_t>(faces.size());
      polymesh->faceStart = new uint32_t[polymesh->numFaces + 1];
      uint32_t faceStart = 0;
      for (uint32_t i = 0; i < polymesh->numFaces; i++) {
        polymesh->faceStart[i] = faceStart;
        faceStart += static_cast<uint32_t>(faces[i].size());
      }
      polymesh->faceStart[polymesh->numFaces] = faceStart;

      polymesh->numIndices = polymesh->faceStart[polymesh->numFaces];
      polymesh->indices = new int[polymesh->numIndices];
      for (uint32_t i = 0; i < polymesh->numFaces; i++) {
        const std::vector<int>& face = faces[i];
        faceStart = polymesh->faceStart[i];
        std::memcpy(polymesh->indices + polymesh->faceStart[i], face.data(), face.size() * sizeof(int));
      }
    }

    timer.stop();
    parsingMSOut = timer.elapsedMS();

    delete polymesh;
    return true;
  }


  // This is based closely on the example code from
  // https://github.com/ddiakopoulos/tinyply/blob/master/source/example.cpp
  //
  // I added handling for extracting face data, with pointers from tinyply's
  // author (thanks Dimitri!). I also added some extra attributes to be
  // extracted if they're present in the input file (normals, tex coords).
  static bool parse_with_tinyply(const char* filename, uint32_t vertsPerFace, double& parsingMSOut)
  {
    Timer timer(true); // true --> autostart the timer.

    PolyMesh* polymesh = nullptr;
    try {
      std::ifstream ss(filename, std::ios::binary);
      if (ss.fail()) {
        throw std::exception();
      }

      tinyply::PlyFile file;
      file.parse_header(ss);

      // Tinyply treats parsed data as untyped byte buffers. See below for examples.
      std::shared_ptr<tinyply::PlyData> vertices, normals, faces, uvs;

      vertices = file.request_properties_from_element("vertex", { "x", "y", "z" });

      bool hasNormals = false;
      try {
        normals = file.request_properties_from_element("vertex", { "nx", "ny", "nz" });
        hasNormals = true;
      }
      catch (const std::exception& /*e*/) {}

      bool hasUVs = false;
      try {
        uvs = file.request_properties_from_element("vertex", { "u", "v" });
        hasUVs = true;
      }
      catch (const std::exception& /*e*/) {}
      if (!hasUVs) {
        try {
          uvs = file.request_properties_from_element("vertex", { "s", "t" });
          hasUVs = true;
        }
        catch (const std::exception& /*e*/) {}
      }
      if (!hasUVs) {
        try {
          uvs = file.request_properties_from_element("vertex", { "texture_u", "texture_v" });
          hasUVs = true;
        }
        catch (const std::exception& /*e*/) {}
      }
      if (!hasUVs) {
        try {
          uvs = file.request_properties_from_element("vertex", { "texture_s", "texture_t" });
          hasUVs = true;
        }
        catch (const std::exception& /*e*/) {}
      }

      // Providing a list size hint (the last argument) is a 2x performance improvement. If you have
      // arbitrary ply files, it is best to leave this 0.
      faces = file.request_properties_from_element("face", { "vertex_indices" }, vertsPerFace);

      file.read(ss);

      if (normals && normals->count != vertices->count) {
        throw std::exception();
      }
      if (uvs && uvs->count != vertices->count) {
        throw std::exception();
      }

      polymesh = new PolyMesh();

      polymesh->numVerts = uint32_t(vertices->count);
      polymesh->pos = new float[polymesh->numVerts * 3];
      if (vertices->t == tinyply::Type::FLOAT32) {
        std::memcpy(polymesh->pos, vertices->buffer.get(), vertices->buffer.size_bytes());
      }
      else {
        fprintf(stderr, "Don't know how to convert to floats for vertices attribute");
        throw std::exception();
      }

      if (normals) {
        polymesh->normal = new float[polymesh->numVerts * 3];
        if (normals->t == tinyply::Type::FLOAT32) {
          std::memcpy(polymesh->normal, normals->buffer.get(), normals->buffer.size_bytes());
        }
        else {
          fprintf(stderr, "Don't know how to convert to floats for normals attribute");
          throw std::exception();
        }
      }

      if (uvs) {
        polymesh->uv = new float[polymesh->numVerts * 2];
        if (uvs->t == tinyply::Type::FLOAT32) {
          std::memcpy(polymesh->uv, uvs->buffer.get(), uvs->buffer.size_bytes());
        }
        else {
          fprintf(stderr, "Don't know how to convert to floats for uvs attribute");
          throw std::exception();
        }
      }

      // tinyply assumes that every face has the same number of vertices. As
      // long as that holds, the code here will load the mesh correctly. If it
      // doesn't then we'll most likely get a very messed-up mesh.
      // Unfortunately there's no way we can handle that case any better.
      polymesh->numFaces = static_cast<uint32_t>(faces->count);
      polymesh->faceStart = new uint32_t[polymesh->numFaces + 1];
      uint32_t faceStart = 0;
      if (vertsPerFace == 0) {
        uint32_t divisor = uint32_t(faces->count) * uint32_t(tinyply::PropertyTable[faces->t].stride);
        if (faces->buffer.size_bytes() % divisor != 0) {
          // This indicates that not all faces had the same number of vertices,
          // which tinyply can't handle. Note that this won't catch *all* cases,
          // it's still possible for the buffer size to be an exact multiple of
          // our divisor when some faces have different numbers of vertices.
          throw std::exception();
        }
        vertsPerFace = uint32_t(faces->buffer.size_bytes() / divisor);
      }
      for (uint32_t i = 0; i < polymesh->numFaces; i++) {
        polymesh->faceStart[i] = faceStart;
        faceStart = vertsPerFace;
      }
      polymesh->faceStart[polymesh->numFaces] = faceStart;

      polymesh->numIndices = polymesh->numFaces * vertsPerFace;
      polymesh->indices = new int[polymesh->numIndices];
      std::memcpy(polymesh->indices, faces->buffer.get(), faces->buffer.size_bytes());
    }
    catch (const std::exception& /*e*/) {
      delete polymesh;
      polymesh = nullptr;
    }

    timer.stop();
    parsingMSOut = timer.elapsedMS();

    if (polymesh == nullptr) {
      return false;
    }
    delete polymesh;
    return true;
  }


  struct RPLYTriMeshBuilder {
    PolyMesh* polymesh = nullptr;
    float* pos      = nullptr; // pointer to the current element in the trimeshes pos array.
    float* normal   = nullptr; // pointer to the current element in the trimeshes normal array.
    float* uv       = nullptr; // pointer to the current element in the trimeshes uv array.

    std::vector<uint32_t> faceStart;
    std::vector<int> meshIndices;

    ~RPLYTriMeshBuilder() {
      delete polymesh;
    }
  };


  static int rply_vertex_pos_cb(p_ply_argument arg)
  {
    RPLYTriMeshBuilder* builder = nullptr;
    ply_get_argument_user_data(arg, reinterpret_cast<void**>(&builder), nullptr);
    *builder->pos = static_cast<float>(ply_get_argument_value(arg));
    builder->pos++;
    return 1;
  }


  static int rply_vertex_normal_cb(p_ply_argument arg)
  {
    RPLYTriMeshBuilder* builder = nullptr;
    ply_get_argument_user_data(arg, reinterpret_cast<void**>(&builder), nullptr);
    *builder->normal = static_cast<float>(ply_get_argument_value(arg));
    builder->normal++;
    return 1;
  }


  static int rply_vertex_uv_cb(p_ply_argument arg)
  {
    RPLYTriMeshBuilder* builder = nullptr;
    ply_get_argument_user_data(arg, reinterpret_cast<void**>(&builder), nullptr);
    *builder->uv = static_cast<float>(ply_get_argument_value(arg));
    builder->uv++;
    return 1;
  }


  static int rply_face_cb(p_ply_argument arg)
  {
    RPLYTriMeshBuilder* builder = nullptr;
    ply_get_argument_user_data(arg, reinterpret_cast<void**>(&builder), nullptr);

    long length, valueIndex;
    ply_get_argument_property(arg, nullptr, &length, &valueIndex);

    builder->meshIndices.push_back(static_cast<int>(ply_get_argument_value(arg)));
    if (valueIndex + 1 == length) {
      builder->faceStart.push_back(static_cast<uint32_t>(builder->meshIndices.size()));
    }
    return 1;
  }


  static bool parse_with_rply(const char* filename, uint32_t vertsPerFace, double& parsingMSOut)
  {
    Timer timer(true); // true --> autostart the timer.

    p_ply_error_cb errorFunc = nullptr;
    long idata = 0;
    void* pdata = nullptr;

    p_ply ply = ply_open(filename, errorFunc, idata, pdata);
    if (!ply) {
      return false;
    }
    if (!ply_read_header(ply)) {
      ply_close(ply);
      return false;
    }

    RPLYTriMeshBuilder builder;
    builder.polymesh = new PolyMesh();

    uint32_t numVerts = uint32_t(ply_set_read_cb(ply, "vertex", "x", rply_vertex_pos_cb, &builder, 0));
    bool ok = numVerts > 0 &&
              (ply_set_read_cb(ply, "vertex", "y", rply_vertex_pos_cb, &builder, 0) > 0) &&
              (ply_set_read_cb(ply, "vertex", "z", rply_vertex_pos_cb, &builder, 0) > 0);
    if (!ok) {
      ply_close(ply);
      return false;
    }
    builder.polymesh->numVerts = numVerts;
    builder.polymesh->pos = new float[numVerts * 3];
    builder.pos = builder.polymesh->pos;

    if (ply_set_read_cb(ply, "vertex", "nx", rply_vertex_normal_cb, &builder, 0) > 0 &&
        ply_set_read_cb(ply, "vertex", "ny", rply_vertex_normal_cb, &builder, 0) > 0 &&
        ply_set_read_cb(ply, "vertex", "nz", rply_vertex_normal_cb, &builder, 0) > 0) {
      builder.polymesh->normal = new float[numVerts * 3];
      builder.normal = builder.polymesh->normal;
    }

    bool hasUV = false;
    if (ply_set_read_cb(ply, "vertex", "u", rply_vertex_uv_cb, &builder, 0) > 0 &&
        ply_set_read_cb(ply, "vertex", "v", rply_vertex_uv_cb, &builder, 0) > 0) {
      hasUV = true;
    }
    else if (ply_set_read_cb(ply, "vertex", "s", rply_vertex_uv_cb, &builder, 0) > 0 &&
             ply_set_read_cb(ply, "vertex", "t", rply_vertex_uv_cb, &builder, 0) > 0) {
      hasUV = true;
    }
    else if (ply_set_read_cb(ply, "vertex", "texture_u", rply_vertex_uv_cb, &builder, 0) > 0 &&
             ply_set_read_cb(ply, "vertex", "texture_v", rply_vertex_uv_cb, &builder, 0) > 0) {
      hasUV = true;
    }
    else if (ply_set_read_cb(ply, "vertex", "texture_s", rply_vertex_uv_cb, &builder, 0) > 0 &&
             ply_set_read_cb(ply, "vertex", "texture_t", rply_vertex_uv_cb, &builder, 0) > 0) {
      hasUV = true;
    }
    if (hasUV) {
      builder.polymesh->uv = new float[numVerts * 3];
      builder.uv = builder.polymesh->uv;
    }

    uint32_t numFaces = uint32_t(ply_set_read_cb(ply, "face", "vertex_indices", rply_face_cb, &builder, 0));
    builder.faceStart.reserve(numFaces + 1); // Reserve enough space for a polygon with 256 vertices, any larger will reallocate.
    if (vertsPerFace != 0) {
      builder.meshIndices.reserve(numFaces * vertsPerFace);
    }
    else {
      builder.meshIndices.reserve(numFaces * 6); // Reserve enough space to handle each face being a quad, just in case. Will grow if more space is needed.
    }
    builder.faceStart.push_back(0);

    if (!ply_read(ply)) {
      ply_close(ply);
      return false;
    }

    ply_close(ply);

    PolyMesh* polymesh = builder.polymesh;
    builder.polymesh = nullptr;

    polymesh->indices = new int[builder.meshIndices.size()];
    memcpy(polymesh->indices, builder.meshIndices.data(), builder.meshIndices.size() * sizeof(int));

    timer.stop();
    parsingMSOut = timer.elapsedMS();

    delete polymesh;

    return true;
  }


  // The code for this function is lightly modified copy of Maciej Halber's mshply_test.c
  // from the ply_io_benchmark project:
  //
  // https://github.com/mhalber/ply_io_benchmark/blob/master/mshply_test.c
  //
  // I've modified it to make it populate the PolyMesh structure we're using
  // for these tests, which is slightly more complex than the one used in the
  // original code. In particular, I've added parsing of normals & tex coords
  // if they're present in the file; and I've adapted it to use msh_ply's built-in
  // support for variable-length faces when necessary.
  static bool parse_with_msh_ply(const char* filename, uint32_t vertsPerFace, double& parsingMSOut)
  {
    Timer timer(true); // true --> autostart the timer

    const char* pos_names[] = { "x", "y", "z" };
    const char* normal_names[] = { "x", "y", "z" };
    const char* uv_names[4][2] = {
      { "u", "v" },
      { "s", "t" },
      { "texture_u", "texture_v" },
      { "texture_s", "texture_t" },
    };
    const char* vertex_indices_names[] = { "vertex_indices" };

    char vertex_name[10] = "vertex";
    char face_name[10] = "face";

    msh_ply_desc_t pos_desc = {};
    pos_desc.element_name = vertex_name;
    pos_desc.property_names = pos_names;
    pos_desc.num_properties = 3;
    pos_desc.data_type = MSH_PLY_FLOAT;

    msh_ply_desc_t normal_desc = {};
    normal_desc.element_name = vertex_name;
    normal_desc.property_names = normal_names;
    normal_desc.num_properties = 3;
    normal_desc.data_type = MSH_PLY_FLOAT;

    msh_ply_desc_t uv_desc = {};
    uv_desc.element_name = vertex_name;
    normal_desc.num_properties = 2;
    normal_desc.data_type = MSH_PLY_FLOAT;

    msh_ply_desc_t face_desc = {};
    face_desc.element_name = face_name;
    face_desc.property_names = vertex_indices_names;
    face_desc.num_properties = 1;
    face_desc.data_type = MSH_PLY_INT32;
    face_desc.list_type = MSH_PLY_UINT32;

    PolyMesh* polymesh = new PolyMesh();
    bool ok = true;
    uint32_t* faceCounts = nullptr;

    size_t numVerts = 0, numNormals = 0, numUVs = 0, numFaces = 0;

    pos_desc.data       = &polymesh->pos;
    pos_desc.data_count = &numVerts;

    normal_desc.data = &polymesh->normal;
    normal_desc.data_count = &numNormals;

    uv_desc.data       = &polymesh->uv;
    uv_desc.data_count = &numUVs;

    face_desc.data       = &polymesh->indices;
    face_desc.data_count = &numFaces;
    if (vertsPerFace == 0) {
      face_desc.list_data = &faceCounts;
    }
    else {
      face_desc.list_size_hint = uint8_t(vertsPerFace);
    }

    msh_ply_t* pf = msh_ply_open( filename, "rb");
    if (pf) {
      // x,y,z -> position
      msh_ply_add_descriptor( pf, &pos_desc );

      // optional nx,ny,nz -> normal
      if (msh_ply_has_properties(pf, &normal_desc)) {
        msh_ply_add_descriptor( pf, &pos_desc );
      }

      // optional texcoords. We try 4 sets of names, picking the first that is present (if any).
      for (int i = 0; i < 4; i++) {
        uv_desc.property_names = uv_names[i];
        if (msh_ply_has_properties(pf, &uv_desc)) {
          msh_ply_add_descriptor(pf, &uv_desc);
          break;
        }
      }

      msh_ply_add_descriptor( pf, &face_desc );
      if (msh_ply_read(pf) != MSH_PLY_NO_ERR) {
        ok = false;
      }

      if ((numNormals != 0 && numNormals != numVerts) ||
          (numUVs != 0 && numUVs != numVerts)) {
        ok = false;
      }

      // By this point msh_ply has filled in our vertex and index data, but we
      // faceCounts, numVerts, numIndices and numFaces are not yet filled in.
      if (ok) {
        polymesh->numVerts = static_cast<uint32_t>(numVerts);
        polymesh->numFaces = static_cast<uint32_t>(numFaces);
        polymesh->faceStart = new uint32_t[polymesh->numFaces + 1];
        if (vertsPerFace == 0) {
          uint32_t faceStart = 0;
          for (uint32_t i = 0; i < polymesh->numFaces; i++) {
            polymesh->faceStart[i] = faceStart;
            faceStart += faceCounts[i];
          }
          polymesh->faceStart[polymesh->numFaces] = faceStart;
          polymesh->numIndices = polymesh->faceStart[polymesh->numFaces];
        }
        else {
          for (uint32_t i = 0; i <= polymesh->numFaces; i++) {
            polymesh->faceStart[i] = vertsPerFace * i;
          }
          polymesh->numIndices = polymesh->numFaces * vertsPerFace;
        }
      }

      msh_ply_close(pf);
    }
    else {
      ok = false;
    }

    timer.stop();
    parsingMSOut = timer.elapsedMS();

    // We have to free the members of PolyMesh here before the destructor runs.
    // `msh_ply` will have used malloc rather than new so the destructor's
    // calls to delete[] won't work.
    if (polymesh->pos != nullptr) {
      free(polymesh->pos);
      polymesh->pos = nullptr;
    }
    if (polymesh->normal != nullptr) {
      free(polymesh->normal);
      polymesh->normal = nullptr;
    }
    if (polymesh->uv != nullptr) {
      free(polymesh->uv);
      polymesh->uv = nullptr;
    }
    if (polymesh->indices != nullptr) {
      free(polymesh->indices);
      polymesh->indices = nullptr;
    }
    if (faceCounts != nullptr) {
      free(faceCounts);
      faceCounts = nullptr;
    }
    delete polymesh;

    return ok;
  }


  static void parse_all(const bool enabled[kNumParsers],
                        bool prewarm,
                        bool verbose,
                        bool precognition,
                        size_t n,
                        Result results[])
  {
    for (size_t i = 0; i < n; i++) {
      const char* filename = results[i].filename.c_str();
      if (verbose) {
        printf("Parsing %s\n", filename);
        fflush(stdout);
      }
      if (prewarm) {
        prewarm_parser(filename);
      }

      uint32_t vertsPerFace = precognition ? verts_per_face(filename) : 0;

      for (uint32_t p = 0; p < kNumParsers; p++) {
        if (!enabled[p]) {
          continue;
        }
        results[i].ok[p] = kParsers[p](filename, vertsPerFace, results[i].msecs[p]);
      }
    }
  }


  static void parse_transposed(const bool enabled[kNumParsers],
                               bool prewarm,
                               bool verbose,
                               bool precognition,
                               size_t n,
                               Result results[])
  {
    if (prewarm) {
      if (verbose) {
        printf("Prewarming %u files\n", uint32_t(n));
      }
      for (size_t i = 0; i < n; i++) {
        const char* filename = results[i].filename.c_str();
        prewarm_parser(filename);
      }
    }

    std::vector<uint32_t> vertsPerFace(n, 0u);
    if (precognition) {
      if (verbose) {
        printf("Getting verts-per-face counts for %u files\n", uint32_t(n));
      }
      for (size_t i = 0; i < n; i++) {
        vertsPerFace[i] = verts_per_face(results[i].filename.c_str());
      }
    }

    for (uint32_t p = 0; p < kNumParsers; p++) {
      if (!enabled[p]) {
        continue;
      }
      if (verbose) {
        printf("Parsing %u files with %s\n", uint32_t(n), kParserNames[p]);
        fflush(stdout);
      }
      for (size_t i = 0; i < n; i++) {
        const char* filename = results[i].filename.c_str();
        results[i].ok[p] = kParsers[p](filename, vertsPerFace[i], results[i].msecs[p]);
      }
    }
  }


  static uint32_t first_enabled(const bool enabled[kNumParsers])
  {
    for (uint32_t i = 0; i < kNumParsers; i++) {
      if (enabled[i]) {
        return i;
      }
    }
    return kNumParsers;
  }


  static bool multiple_parsers_enabled(const bool enabled[kNumParsers])
  {
    bool foundOne = false;
    for (uint32_t i = 0; i < kNumParsers; i++) {
      if (enabled[i]) {
        if (foundOne) {
          return true;
        }
        foundOne = true;
      }
    }
    return false;
  }


  struct OutputOptions {
    int filenameWidth;
    uint32_t baseline;
    bool showSpeedup;
    bool showSlowdown;
  };


  static void print_header(FILE* out, const bool enabled[kNumParsers], const OutputOptions& options)
  {
    fprintf(out, "| %-*s ", options.filenameWidth, "Filename");
    for (uint32_t i = 0; i < kNumParsers; i++) {
      if (!enabled[i]) {
        continue;
      }
      fprintf(out, "| %12s ", kParserNames[i]);
      if (options.showSpeedup) {
        fprintf(out, "%10s ", "(Speedup)");
      }
      if (options.showSlowdown) {
        fprintf(out, "%10s ", "(Slowdown)");
      }
    }
    fprintf(out, "|\n");

    fprintf(out, "| :");
    for (int i = 0; i < options.filenameWidth - 1; i++) {
      fputc('-', out);
    }
    fputc(' ', out);

    for (uint32_t i = 0; i < kNumParsers; i++) {
      if (!enabled[i]) {
        continue;
      }
      fprintf(out, "| -----------");
      if (options.showSpeedup) {
        fprintf(out, "-----------");
      }
      if (options.showSlowdown) {
        fprintf(out, "-----------");
      }
      fprintf(out, ": ");
    }

    fprintf(out, "|\n");
  }


  static void print_result(FILE* out,
                           const Result& result,
                           const bool enabled[kNumParsers],
                           const OutputOptions& options)
  {
    fprintf(out, "| %-*s ", options.filenameWidth, result.filename.c_str());

    char tmp[64];

    for (uint32_t i = 0; i < kNumParsers; i++) {
      if (!enabled[i]) {
        continue;
      }
      fprintf(out, "| ");
      if (result.ok[i]) {
        fprintf(out, "%12.3lf ", result.msecs[i]);
      }
      else {
        fprintf(out, "%12s ", "failed");
      }

      if (options.showSpeedup) {
        if (result.ok[i] && result.ok[options.baseline]) {
          double speedup = result.msecs[options.baseline] / result.msecs[i];
          snprintf(tmp, sizeof(tmp), "(%.2lfx)", speedup);
        }
        else {
          tmp[0] = '\0';
        }
        fprintf(out, "%10s ", tmp);
      }

      if (options.showSlowdown) {
        if (result.ok[i] && result.ok[options.baseline]) {
          double slowdown = result.msecs[i] / result.msecs[options.baseline];
          snprintf(tmp, sizeof(tmp), "(%.2lfx)", slowdown);
        }
        else {
          tmp[0] = '\0';
        }
        fprintf(out, "%10s ", tmp);
      }
    }

    fprintf(out, "|\n");
  }


  static void print_results(FILE* out,
                            const std::vector<Result> results,
                            const bool enabled[kNumParsers],
                            bool showSpeedup,
                            bool showSlowdown)
  {
    OutputOptions outputOptions;

    outputOptions.filenameWidth = 0;
    for (const Result& result : results) {
      int newWidth = static_cast<int>(result.filename.size());
      if (newWidth > outputOptions.filenameWidth) {
        outputOptions.filenameWidth = newWidth;
      }
    }

    if (multiple_parsers_enabled(enabled)) {
      outputOptions.baseline = first_enabled(enabled);
      outputOptions.showSpeedup = showSpeedup;
      outputOptions.showSlowdown = showSlowdown;
    }
    else {
      outputOptions.baseline = kNumParsers;
      outputOptions.showSpeedup = false;
      outputOptions.showSlowdown = false;
    }

    print_header(out, enabled, outputOptions);
    for (const Result& result : results) {
      print_result(out, result, enabled, outputOptions);
    }
  }


  static void print_results_as_csv(FILE* out, const std::vector<Result> results, const bool enabled[kNumParsers])
  {
    fprintf(out, "\"Filename\"");
    for (uint32_t i = 0; i < kNumParsers; i++) {
      if (enabled[i]) {
        fprintf(out, ", \"%s\"", kParserNames[i]);
      }
    }
    fprintf(out, "\n");

    fprintf(out, "\n");

    for (const Result& result : results) {
      fprintf(out, "\"%s\"", result.filename.c_str());

      for (uint32_t i = 0; i < kNumParsers; i++) {
        if (!enabled[i]) {
          continue;
        }

        if (result.ok[i]) {
          fprintf(out, ", %lf", result.msecs[i]);
        }
        else {
          fprintf(out, ", \"failed\"");
        }
      }

      fprintf(out, "\n");
    }
  }


  static bool has_extension(const char* filename, const char* ext)
  {
    int j = int(strlen(ext));
    int i = int(strlen(filename)) - j;
    if (i <= 0 || filename[i - 1] != '.') {
      return false;
    }
    return strcmp(filename + i, ext) == 0;
  }

} // namespace vh


int main(int argc, char** argv)
{
  using namespace vh;

  bool enabled[kNumParsers];
  for (uint32_t i = 0; i < kNumParsers; i++) {
    enabled[i] = true;
  }

  bool prewarm = true;
  bool printAsCSV = false;
  bool verbose = true;
  bool transposed = false;
  bool summary = false;
  bool speedup = false;
  bool slowdown = false;
  bool precognition = false; // when true, run a prepass to determine a verts-per-face value to use for the file.
  const char* outfile = nullptr;

  int argi = 1;
  MatchedOption match;
  while (argi < argc) {
    if (match_option(argc, argv, argi, options, match)) {
      switch (match.id) {
      case eHelp:
        print_help(argv[0], options);
        return 0;

      case eVersion:
        print_version(kTitle, kMajorVersion, kMinorVersion);
        return 0;

      case eNoMiniPLY:
        enabled[eMiniPLY] = false;
        break;

      case eNoHapply:
        enabled[eHapply] = false;
        break;

      case eNoTinyPLY:
        enabled[eTinyPLY] = false;
        break;

      case eNoRPLY:
        enabled[eRPLY] = false;
        break;

      case eNoMSHPly:
        enabled[eMSHPly] = false;
        break;

      case eNoPrewarm:
        prewarm = false;
        break;

      case eCSV:
        printAsCSV = true;
        break;

      case eQuiet:
        verbose = false;
        break;

      case eOutFile:
        parse_option(argc, argv, argi, &options[match.id], &outfile);
        break;

      case eTransposed:
        transposed = true;
        break;

      case eSummary:
        summary = true;
        break;

      case eSpeedup:
        speedup = true;
        break;

      case eSlowdown:
        slowdown = true;
        break;

      case ePrecognition:
        precognition = true;
        break;

      // Handle other options here

      default:
        break;
      }

      remove_matched_option(argc, argv, argi, match);
    }
    else {
      ++argi;
    }
  }
  // All matched options have been removed from argv by this point and argc
  // has been adjusted accordingly. argv[0] is still the executable name.

  if (argc <= 1) {
    fprintf(stderr, "No input files provided.\n");
    return EXIT_SUCCESS;
  }

  // Process the files, building up a table of results. We don't just print the
  // results out as we go because pbrt-parser prints some intermediate output
  // which messes up our formatting.
  const int kFilenameBufferLen = 16 * 1024 - 1;
  char* filenameBuffer = new char[kFilenameBufferLen + 1];
  filenameBuffer[kFilenameBufferLen] = '\0';

  std::vector<Result> results;
  for (int i = 1; i < argc; i++) {
    if (has_extension(argv[i], "txt")) {
      FILE* f = nullptr;
      if (file_open(&f, argv[i], "r") == 0) {
        while (fgets(filenameBuffer, kFilenameBufferLen, f)) {
          results.push_back(Result{});
          results.back().filename = filenameBuffer;
          while (results.back().filename.back() == '\n') {
            results.back().filename.pop_back();
          }
        }
        fclose(f);
      }
      else {
        fprintf(stderr, "Failed to open %s\n", argv[i]);
      }
    }
    else {
      results.push_back(Result{});
      results.back().filename = argv[i];
    }
  }
  delete[] filenameBuffer;

  if (transposed) {
    parse_transposed(enabled, prewarm, verbose, precognition, results.size(), results.data());
  }
  else {
    parse_all(enabled, prewarm, verbose, precognition, results.size(), results.data());
  }
  if (verbose) {
    printf("Parsing complete!\n\n");
  }

  // Add a special result containing the total parsing times for each parser.
  Result overall;
  overall.filename = "Overall Total";
  for (uint32_t p = 0; p < kNumParsers; p++) {
    overall.ok[p] = enabled[p];
    overall.msecs[p] = 0.0;
  }
  for (const Result& result : results) {
    for (uint32_t p = 0; p < kNumParsers; p++) {
      overall.msecs[p] += result.msecs[p];
    }
  }

  if (summary) {
    results.clear();
  }
  results.push_back(overall);

  FILE* out = stdout;
  if (outfile != nullptr) {
    if (file_open(&out, outfile, "w") != 0) {
      fprintf(stderr, "Failed to open output file %s for writing\n", outfile);
      return EXIT_FAILURE;
    }
  }

  if (printAsCSV) {
    print_results_as_csv(out, results, enabled);
  }
  else {
    print_results(out, results, enabled, speedup, slowdown);
  }

  if (out != stdout) {
    fclose(out);
  }

  return EXIT_SUCCESS;
}
