// Copyright 2019 Vilya Harvey
#include <miniply.h>
#include <happly.h>
#include <tinyply.h>

#include <vh_cmdline.h>
#include <vh_time.h>

#include <atomic>
#include <cstdio>
#include <string>
#include <thread>

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
  eNoPrewarm,
  eCSV,
};

static const vh::CommandLineOption options[] = {
  { eHelp,              'h',  "help",       nullptr, nullptr, "Print this help message and exit."                         },
  { eVersion,           'v',  "version",    nullptr, nullptr, "Print the application version and exit."                   },
  { eNoMiniPBRT,        '\0', "no-miniply", nullptr, nullptr, "Disable the \"minpbrt\" parser."                           },
  { eNoThreaded,        '\0', "no-happly",  nullptr, nullptr, "Disable the \"happly\" parser."                            },
  { eNoPBRTParser,      '\0', "no-tinyply", nullptr, nullptr, "Disable the \"tinyply\" parser."                           },
  { eNoPrewarm,         '\0', "no-prewarm", nullptr, nullptr, "Don't pre-warm the disk cache before parsing (useful for very large scenes)." },
  { eCSV,               '\0', "csv",        nullptr, nullptr, "Format output as CSV, for easy import into a spreadsheet." },
  { vh::kUnknownOption, '\0', nullptr,      nullptr, nullptr, nullptr                                                     }
};


namespace vh {

  typedef bool (*ParserFunc)(const char* filename, double& parsingSecsOut);


  static bool prewarm_parser(const char* filename);
  static bool parse_with_miniply(const char* filename, double& parsingSecsOut);
  static bool parse_with_happly(const char* filename, double& parsingSecsOut);
  static bool parse_with_tinyply(const char* filename, double& parsingSecsOut);


  enum ParserID {
    eMiniPLY,
    eHapply,
    eTinyPLY,
  };


  static const char* kParserNames[] = {
    "miniply",
    "happly",
    "tinyply",
  };


  static const ParserFunc kParsers[] = {
    parse_with_miniply,
    parse_with_happly,
    parse_with_tinyply,
  };
  static const uint32_t kNumParsers = sizeof(kParsers) / sizeof(kParsers[0]);


  struct Result {
    std::string filename;
    double secs[kNumParsers];
    bool ok[kNumParsers];
  };


  // This is what we populate to test & benchmark data extraction from the PLY
  // file. It's a triangle mesh, so any faces with more than three verts will
  // get triangulated.
  struct TriMesh {
    // Per-vertex data
    float* pos     = nullptr; // has 3*numVerts elements.
    float* normal  = nullptr; // if non-null, has 3 * numVerts elements.
    float* tangent = nullptr; // if non-null, has 3 * numVerts elements.
    float* uv      = nullptr; // if non-null, has 2 * numVerts elements.
    uint32_t numVerts   = 0;

    // Per-index data
    int* indices   = nullptr;
    uint32_t numIndices = 0; // number of indices = 3 times the number of faces.

    ~TriMesh() {
      delete[] pos;
      delete[] normal;
      delete[] tangent;
      delete[] uv;
      delete[] indices;
    }
  };


  // Read the PLY file so that it's in the OS's disk cache when we run the
  // parsing performance tests. We just read the file into memory without
  // doing any processing on it for these purposes.
  static bool prewarm_parser(const char* filename)
  {
    FILE* f = nullptr;
    if (fopen_s(&f, plymesh->filename, "rb") != 0) {
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


  static bool parse_with_miniply(const char* filename, double& parsingSecsOut)
  {
    Timer timer(true); // true --> autostart the timer.

    miniply::PLYReader reader(filename);
    if (!reader.valid()) {
      return false;
    }

    TriMesh* trimesh = new TriMesh();
    bool gotVerts = false;
    bool gotFaces = false;

    while (reader.has_element() && (!gotVerts || !gotFaces)) {
      const miniply::PLYElement* elem = reader.element();
      if (!gotVerts && strcmp(elem->name.c_str(), "vertex") == 0) {
        if (!reader.load_element()) {
          break; // failed to load data for this element.
        }

        const miniply::PLYElement* elem = reader.element();
        trimesh->numVerts = elem->count;
        trimesh->pos = new float[elem->count * 3];
        if (!reader.extract_vec3("x", "y", "z", trimesh->pos)) {
          break; // invalid data: vertex data MUST include a position
        }

        if (reader.has_vec3("nx", "ny", "nz")) {
          trimesh->normal = new float[elem->count * 3];
          if (!reader.extract_vec3("nx", "ny", "nz", trimesh->normal)) {
            break; // invalid data: couldn't parse normal.
          }
        }

        bool uvsOK = true;
        if (reader.has_vec2("u", "v")) {
          trimesh->uv = new float[elem->count * 2];
          uvsOK = reader.extract_vec2("u", "v", trimesh->uv);
        }
        else if (reader.has_vec2("s", "t")) {
          trimesh->uv = new float[elem->count * 2];
          uvsOK = reader.extract_vec2("s", "t", trimesh->uv);
        }
        else if (reader.has_vec2("texture_u", "texture_v")) {
          trimesh->uv = new float[elem->count * 2];
          uvsOK = reader.extract_vec2("texture_u", "texture_v", trimesh->uv);
        }
        else if (reader.has_vec2("texture_s", "texture_t")) {
          trimesh->uv = new float[elem->count * 2];
          uvsOK = reader.extract_vec2("texture_s", "texture_t", trimesh->uv);
        }
        if (!uvsOK) {
          break; // invalid data, couldn't parse tex coords
        }

        gotVerts = true;
      }
      else if (!gotFaces && strcmp(elem->name.c_str(), "face") == 0) {
        if (!reader.load_element()) {
          break;
        } 

        // Find the indices property.
        uint32_t numIndices = reader.count_triangles("vertex_indices") * 3;
        if (numIndices == 0) {
          break;
        }

        trimesh->numIndices = numIndices;
        trimesh->indices = new int[numIndices];
        if (!reader.extract_triangles("vertex_indices", trimesh->pos, trimesh->numVerts, trimesh->indices)) {
          break; // failed to get triangles
        }

        gotFaces = true;
      }
      reader.next_element();
    }

    if (!gotVerts || !gotFaces) {
      delete trimesh;
      return false;
    }

    timer.stop();
    parsingSecsOut = timer.elapsedSecs();

    delete trimesh;
    return true;
  }


  static bool parse_with_happly(const char* filename, double& parsingSecsOut)
  {
    Timer timer(true); // true --> autostart the timer.

    happly::PLYData plyIn(filename);
    if (!plyIn.hasElement("vertex") || !plyIn.hasElement("face")) {
      return false;
    }

    TriMesh* trimesh = new TriMesh();

    // Load vertex data.
    {
      happly::Element& elem = plyIn.getElement("vertex");
      trimesh->numVerts = uint32_t(elem.count);

      trimesh->pos = new float[trimesh->numVerts * 3];
      std::vector<float> xvals = elem.getProperty<float>("x");
      std::vector<float> yvals = elem.getProperty<float>("y");
      std::vector<float> zvals = elem.getProperty<float>("z");
      for (uint32_t i = 0; i < trimesh->numVerts; i++) {
        trimesh->pos[3 * i    ] = xvals[i];
        trimesh->pos[3 * i + 1] = yvals[i];
        trimesh->pos[3 * i + 2] = zvals[i];
      }

      if (elem.hasProperty("nx") && elem.hasProperty("ny") && elem.hasProperty("nz")) {
        trimesh->normal = new float[trimesh->numVerts * 3];
        xvals = elem.getProperty<float>("nx");
        yvals = elem.getProperty<float>("ny");
        zvals = elem.getProperty<float>("nz");
        for (uint32_t i = 0; i < trimesh->numVerts; i++) {
          trimesh->normal[3 * i    ] = xvals[i];
          trimesh->normal[3 * i + 1] = yvals[i];
          trimesh->normal[3 * i + 2] = zvals[i];
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
        trimesh->uv = new float[trimesh->numVerts * 2];
        for (uint32_t i = 0; i < trimesh->numVerts; i++) {
          trimesh->uv[2 * i    ] = xvals[i];
          trimesh->uv[2 * i + 1] = yvals[i];
        }
      }
    }

    // Load index data.
    {
      std::vector<std::vector<int>> faces = plyIn.getFaceIndices<int>();

      uint32_t numTriangles = 0;
      for (const std::vector<int>& face : faces) {
        if (face.size() < 3) {
          continue;
        }
        numTriangles += uint32_t(face.size() - 2);
      }

      trimesh->numIndices = numTriangles * 3;
      trimesh->indices = new int[trimesh->numIndices];

      int* dst = trimesh->indices;
      for (const std::vector<int>& face : faces) {
        if (face.size() < 3) {
          continue;
        }
        uint32_t faceTris = miniply::triangulate_polygon(uint32_t(face.size()), trimesh->pos, trimesh->numVerts, face.data(), dst);
        dst += (faceTris * 3);
      }
    }

    timer.stop();
    parsingSecsOut = timer.elapsedSecs();

    delete trimesh;
    return true;
  }


  static bool parse_with_tinyply(const char* filename, double& parsingSecsOut)
  {
    Timer timer(true); // true --> autostart the timer.

    TriMesh* trimesh = nullptr;
    try {
      std::ifstream ss(filename, std::ios::binary);
      if (ss.fail()) {
        throw std::runtime_error(std::string("failed to open ") + filename);
      }

      tinyply::PlyFile file;
      file.parse_header(ss);

      // Tinyply treats parsed data as untyped byte buffers. See below for examples.
      std::shared_ptr<tinyply::PlyData> vertices, normals, faces, uvs;
      bool hasNormals = false, hasUVs = false;

      vertices = file.request_properties_from_element("vertex", { "x", "y", "z" });

      try {
        normals = file.request_properties_from_element("vertex", { "nx", "ny", "nz" });
        hasNormals = true;
      }
      catch (const std::exception& /*e*/) {}

      try {
        uvs = file.request_properties_from_element("vertex", { "u", "v" });
        hasUVs = true;
      }
      catch (const std::exception& /*e*/) {
        try {
          uvs = file.request_properties_from_element("vertex", { "s", "t" });
          hasUVs = true;
        }
        catch (const std::exception& /*e*/) {
          try {
            uvs = file.request_properties_from_element("vertex", { "texture_u", "texture_v" });
            hasUVs = true;
          }
          catch (const std::exception& /*e*/) {
            try {
              uvs = file.request_properties_from_element("vertex", { "texture_s", "texture_t" });
              hasUVs = true;
            }
            catch (const std::exception& /*e*/) {}
          }
        }
      }

      // Providing a list size hint (the last argument) is a 2x performance improvement. If you have
      // arbitrary ply files, it is best to leave this 0.
      faces = file.request_properties_from_element("face", { "vertex_indices" }, 0);

      file.read(ss);

      if (normals && normals->count != vertices->count) {
        throw std::exception();
      }
      if (uvs && uvs->count != vertices->count) {
        throw std::exception();
      }

      trimesh = new TriMesh();

      trimesh->numVerts = uint32_t(vertices->count);
      trimesh->pos = new float[trimesh->numVerts * 3];
      if (vertices->t == tinyply::Type::FLOAT32) {
        std::memcpy(trimesh->pos, vertices->buffer.get(), vertices->buffer.size_bytes());
      }
      else {
        fprintf(stderr, "Don't know how to convert to floats for vertices attribute");
        throw std::exception();
      }

      if (normals) {
        trimesh->normal = new float[trimesh->numVerts * 3];
        if (normals->t == tinyply::Type::FLOAT32) {
          std::memcpy(trimesh->normal, normals->buffer.get(), normals->buffer.size_bytes());
        }
        else {
          fprintf(stderr, "Don't know how to convert to floats for normals attribute");
          throw std::exception();
        }
      }

      if (uvs) {
        trimesh->uv = new float[trimesh->numVerts * 2];
        if (uvs->t == tinyply::Type::FLOAT32) {
          std::memcpy(trimesh->uv, uvs->buffer.get(), uvs->buffer.size_bytes());
        }
        else {
          fprintf(stderr, "Don't know how to convert to floats for uvs attribute");
          throw std::exception();
        }
      }

      uint32_t numTriangles = uint32_t(faces->count); // TODO: check for polygons with > 3 verts, recalculate this accordingly.
      trimesh->numIndices = numTriangles * 3;
      trimesh->indices = new int[trimesh->numIndices];

      // TODO: figure out how to extract face data from one of tinyply's buffers.
    }
    catch (const std::exception& /*e*/) {
      delete trimesh;
      trimesh = nullptr;
    }

    timer.stop();
    parsingSecsOut = timer.elapsedSecs();

    return true;
  }


  static void parse(const char* filename, const bool enabled[kNumParsers], bool prewarm, Result& result)
  {
    result.filename = filename;
    if (prewarm) {
      prewarm_parser(filename);
    }
    for (uint32_t p = 0; p < kNumParsers; p++) {
      if (!enabled[p]) {
        continue;
      }
      printf("Parsing %s with %s...\n", filename, kParserNames[p]);
      fflush(stdout);
      result.ok[p] = kParsers[p](filename, result.secs[p]);
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


  static void print_header(int filenameWidth, const bool enabled[kNumParsers], uint32_t baseline)
  {
    bool showSpeedup = baseline < kNumParsers;

    printf("| %-*s ", filenameWidth, "Filename");
    for (uint32_t i = 0; i < kNumParsers; i++) {
      if (!enabled[i]) {
        continue;
      }
      if (showSpeedup && i != baseline) {
        printf("| %12s (Speedup) ", kParserNames[i]);
      }
      else {
        printf("| %12s ", kParserNames[i]);
      }
    }
    printf("|\n");

    printf("| :");
    for (int i = 0; i < filenameWidth - 1; i++) {
      fputc('-', stdout);
    }
    fputc(' ', stdout);

    for (uint32_t i = 0; i < kNumParsers; i++) {
      if (!enabled[i]) {
        continue;
      }
      if (showSpeedup && i != baseline) {
        printf("| ---------------------: ");
      }
      else {
        printf("| -----------: ");
      }
    }

    printf("|\n");

    fflush(stdout);
  }


  static void print_result(const Result& result, int filenameWidth, const bool enabled[kNumParsers], uint32_t baseline)
  {
    bool showSpeedup = baseline < kNumParsers;

    printf("| %-*s ", filenameWidth, result.filename.c_str());

    for (uint32_t i = 0; i < kNumParsers; i++) {
      if (!enabled[i]) {
        continue;
      }
      if (showSpeedup && i != baseline) {
        if (result.ok[i] && result.ok[baseline]) {
          double speedup = result.secs[baseline] / result.secs[i];
          printf("| %12.3lf (%6.2lfx) ", result.secs[i], speedup);
        }
        else if (result.ok[i] && !result.ok[baseline]) {
          printf("| %12.3lf           ", result.secs[i]);
        }
        else {
          printf("| %12s           ", "failed");
        }
      }
      else {
        if (result.ok[i]) {
          printf("| %12.3lf ", result.secs[i]);
        }
        else {
          printf("| %12s ", "failed");
        }
      }
    }

    printf("|\n");
  }


  static void print_results(const std::vector<Result> results, const bool enabled[kNumParsers])
  {
    int filenameWidth = 0;
    for (const Result& result : results) {
      int newWidth = static_cast<int>(result.filename.size());
      if (newWidth > filenameWidth) {
        filenameWidth = newWidth;
      }
    }

    uint32_t baseline = multiple_parsers_enabled(enabled) ? first_enabled(enabled) : kNumParsers;

    print_header(filenameWidth, enabled, baseline);
    for (const Result& result : results) {
      print_result(result, filenameWidth, enabled, baseline);
    }
  }


  static void print_results_as_csv(const std::vector<Result> results, const bool enabled[kNumParsers])
  {
    printf("\"Filename\"");
    for (uint32_t i = 0; i < kNumParsers; i++) {
      if (enabled[i]) {
        printf(", \"%s\"", kParserNames[i]);
      }
    }
    printf("\n");

    printf("\n");

    for (const Result& result : results) {
      printf("\"%s\"", result.filename.c_str());

      for (uint32_t i = 0; i < kNumParsers; i++) {
        if (!enabled[i]) {
          continue;
        }

        if (result.ok[i]) {
          printf(", %lf", result.secs[i]);
        }
        else {
          printf(", \"failed\"");
        }
      }

      printf("\n");
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

      case eNoPrewarm:
        prewarm = false;
        break;

      case eCSV:
        printAsCSV = true;
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

  std::vector<std::string> filenames;
  for (int i = 1; i < argc; i++) {
    if (has_extension(argv[i], "txt")) {
      printf("file %s has extension 'txt'\n", argv[i]);
      FILE* f = nullptr;
      if (fopen_s(&f, argv[i], "r") == 0) {
        while (fgets(filenameBuffer, kFilenameBufferLen, f)) {
          filenames.push_back(filenameBuffer);
          while (filenames.back().back() == '\n') {
            filenames.back().pop_back();
          }
        }
        fclose(f);
      }
      else {
        fprintf(stderr, "Failed to open %s\n", argv[i]);
      }
    }
    else {
      filenames.push_back(argv[i]);
    }
  }

  printf("Parsing these files:\n");
  for (const std::string& filename : filenames) {
    printf("  %s\n", filename.c_str());
  }

  std::vector<Result> results(filenames.size(), Result{});
  for (size_t i = 0; i < filenames.size(); i++) {
    parse(filenames[i].c_str(), enabled, prewarm, results[i]);
  }
  printf("Parsing complete!\n\n");

  if (printAsCSV) {
    print_results_as_csv(results, enabled);
  }
  else {
    print_results(results, enabled);
  }
  return EXIT_SUCCESS;
}
