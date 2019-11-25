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
* These results are from before the `msh_ply` parser was added.

Precognition off:

| Collection        | # files |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :---------------- | ------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| pbrt-v3-scenes    |    8929 |     6901.966    (1.00x) |    31133.146    (4.51x) |    32713.057    (4.74x) |    16190.472    (2.35x) |    11603.855    (1.68x) |
| benedikt-bitterli |    3032 |     1036.978    (1.00x) |     4441.298    (4.28x) |     4537.953    (4.38x) |     2440.391    (2.35x) |     1913.901    (1.85x) |
| Stanford3DScans   |      19 |     3681.125    (1.00x) |    20397.763    (5.54x) |    13961.733    (3.79x) |     7039.228    (1.91x) |     8189.151    (2.22x) |


Precognition on:

| Collection        | # files |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |
| :---------------- | ------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| pbrt-v3-scenes    |    8929 |     4659.166    (1.00x) |    31255.909    (6.71x) |    17367.664    (3.73x) |    16417.979    (3.52x) |     3132.444    (0.67x) |
| benedikt-bitterli |    3032 |      681.167    (1.00x) |     4102.524    (6.02x) |     2248.745    (3.30x) |     2335.888    (3.43x) |      390.444    (0.57x) |
| Stanford3DScans   |      19 |     1674.295    (1.00x) |    20364.224   (12.16x) |     8674.589    (5.18x) |     7316.340    (4.37x) |     2635.912    (1.57x) |


Results - windows
-----------------

* Times are in milliseconds and are for parsing all files in the collection.
* The machine used for these timings was a late-2015 Windows 10 laptop with an SSD and 16 GB of RAM.

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
