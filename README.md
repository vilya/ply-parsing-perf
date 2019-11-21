ply-parsing-perf: Performance comparisons of PLY parsers
========================================================

This project provides a command line app which parses [PLY
files](https://pbrt.org/fileformat-v3.html) using several different parsing
libraries and populates a simply polygon mesh data structure using their
results. It produces a report about how long each parser took. The performance
report can be formatted as Markdown or CSV.

The parsers currently being tested are:

* [Happly](https://github.com/nmwsharp/happly)
* [miniply](https://github.com/vilya/miniply)
* [msh_ply](https://github.com/mhalber/msh)
* [RPly](http://w3.impa.br/~diego/software/rply/)
* [tinyply](https://github.com/ddiakopoulos/tinyply)

Detailed results from running this tool can be found in the results-\* 
subdirectories. If you just want the high-level overview, see below.

*Disclaimer:* The author of this tool is also the author of the `miniply`
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

* Times are in milliseconds, for parsing all files in the collection.
* The machine used for these timings was a 2015 MacBook Pro.


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



