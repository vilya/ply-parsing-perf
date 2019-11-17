cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0091 NEW)

project(ply-parsing-perf)

set(CMAKE_CXX_STANDARD 11)
if(MSVC)
  set(CMAKE_CXX_FLAGS "/EHsc")
#  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
endif(MSVC)


# Include root for our own sources
include_directories(src)

# miniply
include_directories(3rdparty/miniply)

# happly
include_directories(3rdparty/happly)

# tinyply
include_directories(3rdparty/tinyply/source)

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
  3rdparty/tinyply/source/tinyply.h
  3rdparty/tinyply/source/tinyply.cpp

  # pieces source files
  3rdparty/pieces/vh_cmdline.cpp
  3rdparty/pieces/vh_cmdline.h
  3rdparty/pieces/vh_time.cpp
  3rdparty/pieces/vh_time.h
)
