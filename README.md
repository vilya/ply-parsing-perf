ply-parsing-perf: Performance comparisons of PLY parsers
========================================================

This project provides a command line app which parses [PLY
files](https://pbrt.org/fileformat-v3.html) using several different parsing
libraries and populates a simply polygon mesh data structure using their
results. It produces a report about how long each parser took. The performance
report can be formatted as Markdown or CSV.


The task
--------

We measure performance by using each of the parsers to load a PLY file and
populate a simply polygon mesh structure. We do this for every file the user
specifies on the command line. 

The mesh structure that we're populating is:

```cpp
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
  };
```

Each parser must populate the `pos`, `indices` and `faceStart` arrays. The
`normal` and `uv` arrays must be populated too if the input file contains data
for them.

This task was chosen because it's quite similar (though simplified) to the use
case that I originally needed a PLY parser for: loading a scene which uses
(potentially lots of) PLY files to store all the geometry. 

Note that we're loading a polygon mesh rather than a triangle mesh because my
test data set contains quite a few PLY files that are quad meshes - or a mix
of triangles and quads - and I didn't want the overhead of a polygon
triangulation routine in the benchmark. Most ply libraries don't ship their
own polygon triangulation code (miniply being the exception) so I'd just be
benchmarking that same code against itself over and over.


The parsers
-----------

The parsers currently being tested are:

* [Happly](https://github.com/nmwsharp/happly)
* [miniply](https://github.com/vilya/miniply)
* [msh_ply](https://github.com/mhalber/msh)
* [RPly](http://w3.impa.br/~diego/software/rply/)
* [tinyply](https://github.com/ddiakopoulos/tinyply)

Detailed results from running this tool can be found in the results-\* 
subdirectories. If you just want the high-level overview, see below.

*Disclaimer:* The author of this benchmark is also the author of the `miniply`
library. Every effort has been made to keep the performance comparisons as
fair as possible, but the usage of miniply may be better optimised simply due
to better familiarity. Any improvements to the code will be gratefully
received!

The code for this performance testing tool uses the MIT license, but the
parsing libraries it uses are each subject to their own licenses.


Parser Notes
------------

* `tinyply` only has partial support for list properties: it assumes all lists
  belonging to the same property will have the same number of entries. It will 
  not produce a correct mesh for any PLY files where this doesn't hold and may
  crash. We currently use a simple check to detect most of these cases and flag
  the run as failed, but it is still possible for a mesh to pass this check
  while it has varying numbers of vertices per face.

* The `RPly` code relies on the order of vertex properties being sensible. Any
  properties loaded as a group (e.g. "x", "y" and "z" for vertex position), 
  must be in the same order in the file as they are expected by the mesh 
  structure, otherwise the mesh will be incorrect. This is not an error that the
  perf testing code can detect (yet) so the results will still be reported as if 
  they were correct. Hopefuly this will be pretty rare though...!


Results - macOS
---------------

* Times are in milliseconds and are for parsing all files in the collection.
* The machine used for these timings was a 2015 MacBook Pro.
* These results are from before the `msh_ply` parser was added.

Precognition off:

| Collection        | # files |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |
| :---------------- | ------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| pbrt-v3-scenes    |    8929 |     6611.270    (1.00x) |    31311.724    (4.74x) |    33409.867    (5.05x) |    16644.463    (2.52x) |
| benedikt-bitterli |    3032 |      963.205    (1.00x) |     4376.803    (4.54x) |     4518.625    (4.69x) |     2437.782    (2.53x) |
| Stanford3DScans   |      19 |     3936.760    (1.00x) |    20454.107    (5.20x) |    14052.630    (3.57x) |     7063.514    (1.79x) |


Precognition on:

| Collection        | # files |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |
| :---------------- | ------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| pbrt-v3-scenes    |    8929 |     4610.583    (1.00x) |    31010.701    (6.73x) |    17441.875    (3.78x) |    16614.581    (3.60x) |
| benedikt-bitterli |    3032 |      691.032    (1.00x) |     4179.267    (6.05x) |     2307.704    (3.34x) |     2400.707    (3.47x) |
| Stanford3DScans   |      19 |     1798.322    (1.00x) |    20462.569   (11.38x) |     8717.252    (4.85x) |     7356.816    (4.09x) |


Results - windows
-----------------

* Times are in milliseconds and are for parsing all files in the collection.
* The machine used for these timings was a late-2015 Windows 10 laptop with SSD and 16 GB of RAM.

Precognition off:


Precognition on:
