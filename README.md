ply-parsing-perf: Performance comparisons of PLY parsers
========================================================

This project provides a command line app which parses [PLY
files](https://pbrt.org/fileformat-v3.html) using several different parsing
libraries and populates a simply polygon mesh data structure using their
results. It produces a report about how long each parser took. The performance
report can be formatted as Markdown or CSV.

The parsers currently being tested are:
* [miniply](https://github.com/vilya/miniply)
* [Happly](https://github.com/nmwsharp/happly)
* [tinyply](https://github.com/ddiakopoulos/tinyply)
* [RPly](http://w3.impa.br/~diego/software/rply/)

See RESULTS.md for one (very large) set of results from running this tool.

*Disclaimer:* The author of this tool is also the author of the `miniply`
library. Every effort has been made to keep the performance comparisons as
fair as possible, but the usage of miniply may be better optimised simply due
to better familiarity. Any improvements to the code will be gratefully
received!

The code for this performance testing tool uses the MIT license, but the
parsing libraries it uses are each subject to their own licenses.


Notes
-----

* `tinyply` only has partial support for list properties: it assumes all lists
  belonging to the same property will have the same number of entries. It will 
  not produce a correct mesh for any PLY files where this doesn't hold. 
  Unfortunately the perf testing code can't detect when the mesh is incorrect,
  so the results will still be reported as though it was correct.

* The `RPly` code relies on the order of vertex properties being sensible. Any 
  properties loaded as a group (e.g. "x", "y" and "z" for vertex position), 
  must be in the same order in the file as they are expected by the mesh 
  structure, otherwise the mesh will be incorrect. Again, this is not an error
  that the perf testing code can detect so the results will still be reported
  as if they were correct.
