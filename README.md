ply-parser-perf: Performance comparisons of PLY parsers
=======================================================

This project provides a command line app which parses 
[PLY files](https://pbrt.org/fileformat-v3.html) using several different
parsing libraries and produces a report about how long each parser took. The
performance report can be formatted as Markdown or CSV.

The parsers currently being tested are:
* [miniply](https://github.com/vilya/miniply)
* [happly](https://github.com/nmwsharp/happly)
* [tinyply](https://github.com/ddiakopoulos/tinyply)

See RESULTS.md for one (fairly large) set of results from running this tool.

The author of this tool is also the author of the `miniply` library. Every
effort has been made to keep the performance comparisons as fair as possible,
but the usage of miniply may be better optimised simply due to better
familiarity. Any improvements to the code will be gratefully received!

The code for this performance testing tool uses the MIT license, but the
parsing libraries it uses are each subject to their own licenses.