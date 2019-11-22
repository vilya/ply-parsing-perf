cmake_minimum_required(VERSION 3.5)

project(ply-parsing-perf)


# Include root for our own sources
include_directories(src)

# miniply
include_directories(3rdparty/miniply)

# happly
include_directories(3rdparty/happly)

# tinyply
include_directories(3rdparty/tinyply/source)

# rply
include_directories(3rdparty/rply-1.1.4)

# msh_ply
include_directories(3rdparty/msh)

# pieces
include_directories(3rdparty/pieces)


# 
# Define our executable
# 

add_executable(ply-parsing-perf
  src/main.cpp

  # miniply source files
  3rdparty/miniply/miniply.cpp
  3rdparty/miniply/miniply.h

  # happly source files
  3rdparty/happly/happly.h

  # tinyply source files
  3rdparty/tinyply/source/tinyply.cpp
  3rdparty/tinyply/source/tinyply.h

  # rply source files
  3rdparty/rply-1.1.4/rply.c
  3rdparty/rply-1.1.4/rply.h
  3rdparty/rply-1.1.4/rplyfile.h

  # pieces source files
  3rdparty/pieces/vh_cmdline.cpp
  3rdparty/pieces/vh_cmdline.h
  3rdparty/pieces/vh_time.cpp
  3rdparty/pieces/vh_time.h
)
