ply-parser-perf: Performance comparisons of PLY parsers
=======================================================

This project provides a command line app which parses 
[PLY files](https://pbrt.org/fileformat-v3.html) using several different
parsing libraries and produces a report about how long each parser took. The
performance report can be formatted as Markdown or CSV.

The parsers currently being tested are:
* [miniply](https://github.com/vilya/miniply)
* [Happly](https://github.com/nmwsharp/happly)
* [tinyply](https://github.com/ddiakopoulos/tinyply)
* [RPly](http://w3.impa.br/~diego/software/rply/)

See RESULTS.md for one (very large) set of results from running this tool.

The author of this tool is also the author of the `miniply` library. Every
effort has been made to keep the performance comparisons as fair as possible,
but the usage of miniply may be better optimised simply due to better
familiarity. Any improvements to the code will be gratefully received!

The code for this performance testing tool uses the MIT license, but the
parsing libraries it uses are each subject to their own licenses.


Notes
-----

* I haven't been able to figure out how to extract face data from tinyply yet,
  so its times do not include any time required to triangulate the faces.

* All parsers (apart from tinyply, see above) use miniply's triangulation code
  on polygons with more than 3 vertices. The times given here include that.

* The test code for miniply and RPly relies on the order of elements in the
  input file: the vertex element must come before the face element if any faces
  need to be triangulated, otherwise triangulation will fail.

* Additionally, the RPly code relies on the order of vertex properties or the
  results will be incorrect:
  * The properties `x`, `y` and `z` must appear in that order, although they
    don't have to be contiguous.
  * If there are vertex normals, `nx`, `ny` and `nz` must appear in that
    order.
  * There are 4 different sets of names that we recognise for UVs. In order of 
    priority:
  	1. `u` and `v`.
  	2. `s` and `t`.
  	3. `texture_u` and `texture_v`.
  	4. `texture_s` and `texture_v`.
  	For any given one of those sets, the properties must appear in the order
  	above. If the model has properties from more than one of those sets, the
  	results will most likely be incorrect and it may cause a seg fault.
