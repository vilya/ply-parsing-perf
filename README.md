ply-parsing-perf: Performance comparisons of PLY parsers
========================================================

This project provides a command line app which parses [PLY
files](https://pbrt.org/fileformat-v3.html) using several different parsing
libraries and populates a simple polygon mesh data structure using their
results. It produces a report about how long each parser took. The performance
report can be formatted as Markdown or CSV.


The task
--------

We measure performance by using each of the parsers to load a PLY file and
populate a simple polygon mesh structure. We do this for every file the user
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

The parsers currently being tested, in alphabetical order:

* [Happly](https://github.com/nmwsharp/happly)
* [miniply](https://github.com/vilya/miniply)
* [msh_ply](https://github.com/mhalber/msh)
* [RPly](http://w3.impa.br/~diego/software/rply/)
* [tinyply](https://github.com/ddiakopoulos/tinyply)

Detailed results from running this tool on a few different computers can be 
found in the results-\* subdirectories. If you just want the high-level overview,
see below.

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
  the run as failed, but the test isn't 100% accurate: it's unlikely but still 
  possible for a mesh to pass the test while having varying numbers of vertices
  per face.

* The `RPly` code relies on the order of vertex properties being sensible. Any
  properties loaded as a group (e.g. "x", "y" and "z" for vertex position), 
  must be in the same order in the file as they are expected by the mesh 
  structure, otherwise the mesh will be incorrect. This is not an error that the
  perf testing code can detect (yet) so the results will still be reported as if 
  they were correct. Hopefuly this will be pretty rare though...!


"Precognition"
--------------

When all faces in a PLY file have the same number of vertices, some parsers 
(`miniply`, `tinyply` and `msh_ply`) can take advantage of that to parse the
file much more efficiently.

In general, because we're parsing an unknown set of files, we cannot know in
advance how many vertices each face in a given file will have. But there are
some important use cases where you might have this knowledge - for example 
when the PLY files are being generated as an intermediate step in your data
pipeline - so we want to be able to benchmark the parsing in that case too (and
give each parser a chance to really shine).

Precognition mode simulates having that knowledge by pre-parsing each input
file and inspecting its face list.

Add `--precognition` on the command line to enable precognition mode.

I called it precognition because it's kind of like letting the parsers see
into the future in a limited way. :-)


Normal vs. transposed parsing
-----------------------------

This is to do with the order in which we process the files with each parser.

"Normal" mode is:
```
for each file:
  for each parser:
    parse file
```

whereas "Transposed" mode is:
```
for each parser:
  for each file:
    parse file
```


Prewarming
----------

The results in this benchmark are heavily influenced by whether the file is
already in the OS's file cache or not. This means whichever parser runs first
may be at a disadvantage because its input file may not yet be cached, but
parsing it will mean that it is cached by the time we run all the other
parsers.

The benchmark works around this by warming up the file cache before running
any of the parsers on a given input file. It streams the entire file into
memory without attempting to do any parsing, just to make sure it's in the
disk cache.

You can disable this behaviour with the `--no-prewarm` option.

This behaves slightly differently when parsing in transposed mode. In this
case we run the prewarm step oncce for all files before running any of the
parsers.


"Slowdown"
----------

As well as reporting the raw parsing times, the benchmark can also display a
"slowdown" factor. This is the ratio of the time for parser *n* to the time
for parser *0*.

Parser 0 is miniply by default, but you can disable this and any of the other
parsers using command line options.


Results - macOS
---------------

* Times are in milliseconds and are for parsing all files in the collection.
* The machine used for these timings was a 2015 MacBook Pro.
* Prewarming is **on** for all of these runs.


Precognition off, normal mode:

`ply-parsing-perf --summary --quiet --slowdown allplyfiles.txt`

| Collection        | # files |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :---------------- | ------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| pbrt-v3-scenes    |    8929 |     6494.546    (1.00x) |    31451.409    (4.84x) |    12200.113    (1.88x) |    16243.463    (2.50x) |    12747.547    (1.96x) |
| benedikt-bitterli |    3032 |     1022.206    (1.00x) |     4466.136    (4.37x) |     1811.638    (1.77x) |     2400.264    (2.35x) |     2084.739    (2.04x) |
| Stanford3DScans   |      19 |     3077.911    (1.00x) |    20386.191    (6.62x) |     2177.027    (0.71x) |     7060.756    (2.29x) |     8183.040    (2.66x) |


Precognition off, transposed mode:

`ply-parsing-perf --summary --quiet --slowdown --transposed allplyfiles.txt`

| Collection        | # files |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :---------------- | ------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| pbrt-v3-scenes    |    8929 |     5128.564    (1.00x) |    30142.863    (5.88x) |    11485.910    (2.24x) |    16078.137    (3.14x) |    15578.443    (3.04x) |
| benedikt-bitterli |    3032 |      765.991    (1.00x) |     4204.140    (5.49x) |     1649.915    (2.15x) |     2331.773    (3.04x) |     2178.850    (2.84x) |
| Stanford3DScans   |      19 |     3137.996    (1.00x) |    20646.780    (6.58x) |     2192.300    (0.70x) |     7125.185    (2.27x) |     8370.152    (2.67x) |


Precognition on, normal mode:

`ply-parsing-perf --summary --quiet --slowdown --precognition allplyfiles.txt`

| Collection        | # files |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :---------------- | ------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| pbrt-v3-scenes    |    8929 |     4802.874    (1.00x) |    31179.455    (6.49x) |    28000.275    (5.83x) |    16326.010    (3.40x) |     4269.351    (0.89x) |
| benedikt-bitterli |    3032 |      819.693    (1.00x) |     4447.801    (5.43x) |     3885.596    (4.74x) |     2430.370    (2.96x) |      594.798    (0.73x) |
| Stanford3DScans   |      19 |     1673.340    (1.00x) |    20410.081   (12.20x) |    10220.413    (6.11x) |     7291.008    (4.36x) |     2727.338    (1.63x) |


Precognition off, transposed mode:

`ply-parsing-perf --summary --quiet --slowdown --transposed --precognition allplyfiles.txt`

| Collection        | # files |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :---------------- | ------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| pbrt-v3-scenes    |    8929 |     4251.458    (1.00x) |    30337.103    (7.14x) |    27967.107    (6.58x) |    16300.324    (3.83x) |     5584.046    (1.31x) |
| benedikt-bitterli |    3032 |      690.395    (1.00x) |     4170.307    (6.04x) |     3800.539    (5.50x) |     2363.405    (3.42x) |      720.316    (1.04x) |
| Stanford3DScans   |      19 |     1722.956    (1.00x) |    20731.954   (12.03x) |    10431.094    (6.05x) |     7337.943    (4.26x) |     2866.534    (1.66x) |


Results - windows
-----------------

* Times are in milliseconds and are for parsing all files in the collection.
* The machine used for these timings was a late-2015 Windows 10 laptop with an SSD and 16 GB of RAM.
* Prewarming is **on** for all of these runs.


Precognition off, normal mode:

`ply-parsing-perf --summary --quiet --slowdown allplyfiles.txt`

| Collection        | # files |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :---------------- | ------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| pbrt-v3-scenes    |    8929 |     5859.284    (1.00x) |    42870.099    (7.32x) |    19615.391    (3.35x) |    20998.883    (3.58x) |    12308.984    (2.10x) |
| benedikt-bitterli |    3032 |      959.554    (1.00x) |     5851.017    (6.10x) |     3019.552    (3.15x) |     3132.636    (3.26x) |     1962.630    (2.05x) |
| Stanford3DScans   |      19 |     3180.575    (1.00x) |    31028.100    (9.76x) |     3762.546    (1.18x) |     8837.733    (2.78x) |     8118.433    (2.55x) |


Precognition off, transposed mode:

`ply-parsing-perf --summary --quiet --slowdown --transposed allplyfiles.txt`

| Collection        | # files |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :---------------- | ------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| pbrt-v3-scenes    |    8929 |     5331.383    (1.00x) |    42759.929    (8.02x) |    19260.840    (3.61x) |    20868.088    (3.91x) |    12517.266    (2.35x) |
| benedikt-bitterli |    3032 |      765.058    (1.00x) |     5528.888    (7.23x) |     2821.783    (3.69x) |     3122.637    (4.08x) |     2033.217    (2.66x) |
| Stanford3DScans   |      19 |     3183.265    (1.00x) |    30710.473    (9.65x) |     3945.928    (1.24x) |     8799.330    (2.76x) |     8088.875    (2.54x) |


Precognition on, normal mode:

`ply-parsing-perf --summary --quiet --slowdown --precognition allplyfiles.txt`

| Collection        | # files |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :---------------- | ------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| pbrt-v3-scenes    |    8929 |     3809.077    (1.00x) |    42443.840   (11.14x) |    52463.472   (13.77x) |    21078.821    (5.53x) |     5591.698    (1.47x) |
| benedikt-bitterli |    3032 |      594.204    (1.00x) |     6312.924   (10.62x) |     8143.940   (13.71x) |     3427.564    (5.77x) |      888.515    (1.50x) |
| Stanford3DScans   |      19 |     2203.132    (1.00x) |    30869.200   (14.01x) |    18160.157    (8.24x) |     9236.321    (4.19x) |     3871.445    (1.76x) |


Precognition off, transposed mode:

`ply-parsing-perf --summary --quiet --slowdown --transposed --precognition allplyfiles.txt`

| Collection        | # files |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :---------------- | ------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| pbrt-v3-scenes    |    8929 |     3819.788    (1.00x) |    42954.578   (11.25x) |    52471.757   (13.74x) |    21307.067    (5.58x) |     6055.684    (1.59x) |
| benedikt-bitterli |    3032 |      495.983    (1.00x) |     5672.085   (11.44x) |     7293.072   (14.70x) |     3172.696    (6.40x) |      915.860    (1.85x) |
| Stanford3DScans   |      19 |     2210.758    (1.00x) |    31019.028   (14.03x) |    18103.653    (8.19x) |     9222.461    (4.17x) |     3835.744    (1.74x) |


Lines of code
-------------

This is how many lines of code it takes to call each of the parsers in
ply-parsing-perf's `main.cpp`. This is the number of lines between the opening
and closing brace of each of the `parse_with_foo` functions, plus (in the case
of rply) the line count for any additional supporting functions & data types. 

This is a very rough measure. It includes blank lines, comments, and
punctuation-only lines. It also includes some code specific to this particular
benchmark, such as handling precognition mode 

So take it with a pinch of salt. :-)

| Parser  | # lines |
| :------ | ------: |
| miniply |      93 |
| happly  |      93 |
| tinyply |     140 |
| rply    |     139 |
| msh_ply |     155 |


Points of interest
------------------

* The fastest parser overall (for this workload) is **miniply** with
  **msh_ply** a fairly close second.

* Both **happly** and **tinyply** are a lot slower on Windows than on macOS. I
  think this is largely due to differences between Microsoft's standard library
  implementation and Clang's: both parsers make heavy use of iostreams and 
  Microsoft's implementation of this in particular is quite slow.

* In terms of shortest calling code, **happly** and **miniply** are equal
  best, but the way you use each of them is very different. With **happly** we
  load the entire file into memory then copy the data into our own structure.
  With **miniply** we load enough info to preallocate our data structure then
  have the parser populate it for us. **happly** is probably easier to get 
  started with, but **miniply** is a lot faster and has a much lower memory 
  overhead.

* Both **rply** and **msh_ply** are written in C. The other parsers are all 
  written in C++.

* **miniply** lacks support for writing PLY files. The other libraries all 
  support this.
