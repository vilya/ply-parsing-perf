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
* Side note: I don't think it's very useful having separate results for with/without `--transpose`, so from now on I'll only be reporting the results *with* `--transpose` (since that tends to complete slightly faster).

Precognition off:

`ply-parsing-perf --summary --quiet --slowdown --transposed allplyfiles.txt`

| Collection        | # files |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :---------------- | ------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| pbrt-v3-scenes    |    8929 |     5515.002    (1.00x) |    31222.484    (5.66x) |       failed            |    16541.212    (3.00x) |       failed            |
| benedikt-bitterli |    3032 |      895.132    (1.00x) |     4787.173    (5.35x) |     4696.567    (5.25x) |     2416.190    (2.70x) |     2230.027    (2.49x) |
| Stanford3DScans   |      19 |     3276.957    (1.00x) |    21286.562    (6.50x) |    15143.252    (4.62x) |     7184.140    (2.19x) |       failed            |


Precognition on:

`ply-parsing-perf --summary --quiet --slowdown --transposed --precognition allplyfiles.txt`

| Collection        | # files |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :---------------- | ------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| pbrt-v3-scenes    |    8929 |     4351.515    (1.00x) |    31213.065    (7.17x) |       failed            |    16807.505    (3.86x) |     6171.157    (1.42x) |
| benedikt-bitterli |    3032 |      718.077    (1.00x) |     4351.638    (6.06x) |     2432.901    (3.39x) |     2437.301    (3.39x) |      749.915    (1.04x) |
| Stanford3DScans   |      19 |     1873.967    (1.00x) |    20924.666   (11.17x) |     8977.394    (4.79x) |     7414.921    (3.96x) |     2935.719    (1.57x) |


Results - windows
-----------------

* Times are in milliseconds and are for parsing all files in the collection.
* The machine used for these timings was a late-2015 Windows 10 laptop with an SSD and 16 GB of RAM.
* Prewarming is **on** for all of these runs.
* Side note: As with the macOS results, I'll only be reporting the results *with* `--transpose` from now on.


Precognition off:

`ply-parsing-perf --summary --quiet --slowdown --transposed allplyfiles.txt`

| Collection        | # files |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :---------------- | ------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| pbrt-v3-scenes    |    8929 |     5664.282    (1.00x) |    42994.899    (7.59x) |       failed            |    20814.662    (3.67x) |       failed            |
| benedikt-bitterli |    3032 |     1100.449    (1.00x) |     6834.284    (6.21x) |       failed            |     3589.032    (3.26x) |     2659.700    (2.42x) |
| Stanford3DScans   |      19 |     4457.512    (1.00x) |    42897.231    (9.62x) |       failed            |    12313.650    (2.76x) |       failed            |


Precognition on:

`ply-parsing-perf --summary --quiet --slowdown --transposed --precognition allplyfiles.txt`

| Collection        | # files |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :---------------- | ------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| pbrt-v3-scenes    |    8929 |     4119.678    (1.00x) |    43254.123   (10.50x) |       failed            |    21596.381    (5.24x) |     6125.734    (1.49x) |
| benedikt-bitterli |    3032 |      495.838    (1.00x) |     5704.487   (11.50x) |     7352.396   (14.83x) |     3173.690    (6.40x) |      903.588    (1.82x) |
| Stanford3DScans   |      19 |     2243.364    (1.00x) |    30821.248   (13.74x) |    18205.596    (8.12x) |     9188.890    (4.10x) |     3823.178    (1.70x) |


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
