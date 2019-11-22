TO DO
=====

* Add all the additional PLY parsers from [ply_io_benchmark](https://github.com/mhalber/ply_io_benchmark).
  * [ ] turkply (broken link, haven't found a copy of it yet).
  * [ ] bourkeply
  * [x] msh_ply
  * [ ] nanoply
  * [ ] plylib
  * [ ] tinyply21 (and older & slower version of the tinyply I already have, should I bother including it?)

* Print out info about how many files failed to load with each parser.

* Calculate a throughput value for each parser
  * Total size of all files which successfully parsed, divided by the total
    time it took to parse them.
  * Display this value as part of the summary.

* Only provide summary info by default, with options to drill down for specific
  files.
  * Group files by directory?

* Option to produce graphs of the results as SVG files.

* Option to load each file more than once with each parser and keep the best result. 

* Stop using submodules for the parsers?
  * It can be a bit of a hassle when any of the submodules is getting regilar updates. 
  * Copy all the parsers into the repo instead?
  
* Set up continuous integration.
