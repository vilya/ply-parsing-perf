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


"Precognition"
--------------

Some parsers (`miniply`, `tinyply` and `msh_ply`) are able to take advantage
of the fact that all faces in a PLY file have the same number of vertices to
parse much more efficiently. 

In general, because we're parsing an unknown set of files, we cannot know in
advance how many vertices each face in a given file will have. But there are
many possible use cases where you will have this knowledge, so we want to be
able to benchmark the parsing in that case too - and each parser a chance to
really shine!

Precognition mode simulates having that knowledge by pre-parsing each input
file and inspecting its face list to determine how many vertices each face has
(and whether they're all the same, or a mix of different sizes).

Add "--precognition" on the command line to enable precognition mode.

I called it precognition because it's kind of like letting the parsers see
into the future in a limited way. :-)


Results - macOS
---------------

* Times are in milliseconds and are for parsing all files in the collection.
* The machine used for these timings was a 2015 MacBook Pro.

Precognition off:

| Collection        | # files |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :---------------- | ------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| pbrt-v3-scenes    |    8929 |     6838.027    (1.00x) |    31077.032    (4.54x) |    32362.829    (4.73x) |    16190.874    (2.37x) |    12732.350    (1.86x) |
| benedikt-bitterli |    3032 |     1051.712    (1.00x) |     4444.430    (4.23x) |     4529.466    (4.31x) |     2440.715    (2.32x) |     2083.407    (1.98x) |
| Stanford3DScans   |      19 |     3737.122    (1.00x) |    20434.039    (5.47x) |    13985.160    (3.74x) |     7038.619    (1.88x) |     8196.966    (2.19x) |


Precognition on:

| Collection        | # files |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :---------------- | ------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| pbrt-v3-scenes    |    8929 |     4712.437    (1.00x) |    31367.663    (6.66x) |    17372.192    (3.69x) |    16392.887    (3.48x) |     4279.931    (0.91x) |
| benedikt-bitterli |    3032 |      691.728    (1.00x) |     4158.252    (6.01x) |     2298.285    (3.32x) |     2402.375    (3.47x) |      570.404    (0.82x) |
| Stanford3DScans   |      19 |     1715.916    (1.00x) |    20438.446   (11.91x) |     8685.205    (5.06x) |     7356.329    (4.29x) |     2633.932    (1.54x) |


Results - windows
-----------------

* Times are in milliseconds and are for parsing all files in the collection.
* The machine used for these timings was a late-2015 Windows 10 laptop with an SSD and 16 GB of RAM.
* TODO: the msh_ply times are from a buggy version of the testing code where it was skipping the normal and UV columns, need to rerun these.

Precognition off:

| Collection        | # files |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :---------------- | ------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| pbrt-v3-scenes    |    8929 |     6475.720    (1.00x) |    44174.730    (6.82x) |    57096.736    (8.82x) |    21309.687    (3.29x) |    11089.668    (1.71x) |
| benedikt-bitterli |    3097 |      951.522    (1.00x) |     5843.121    (6.14x) |     7969.029    (8.38x) |     3168.412    (3.33x) |     1789.941    (1.88x) |
| Stanford3DScans   |      19 |     4265.996    (1.00x) |    33755.121    (7.91x) |    27523.052    (6.45x) |     9265.776    (2.17x) |     8746.675    (2.05x) |


Precognition on:

| Collection        | # files |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :---------------- | ------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| pbrt-v3-scenes    |    8929 |     3895.514    (1.00x) |    44229.690   (11.35x) |    30956.799    (7.95x) |    21781.691    (5.59x) |     4545.359    (1.17x) |
| benedikt-bitterli |    3097 |      538.755    (1.00x) |     5790.756   (10.75x) |     4202.027    (7.80x) |     3192.133    (5.93x) |      648.820    (1.20x) |
| Stanford3DScans   |      19 |     2243.040    (1.00x) |    34014.823   (15.16x) |    17020.522    (7.59x) |     9780.114    (4.36x) |     4351.478    (1.94x) |
