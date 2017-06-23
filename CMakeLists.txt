# CMake build instructions for Dreamshows engine

# configure cmake
cmake_minimum_required(VERSION 3.1)
cmake_policy(SET CMP0004 OLD)

# we require C++11 - this set appropriate flags for compilers, which may not be portable
set(CMAKE_CXX_STANDARD 11)

project(Dreamshows-engine)

# Version
set(DSSE_VERSION_MAJOR 0)
set(DSSE_VERSION_MINOR 1)
set(DSSE_VERSION_PATCH 0)
set(DSSE_VERSION_STR "${DSSE_VERSION_MAJOR}.${DSSE_VERSION_MINOR}.${DSSE_VERSION_PATCH}")
message("Library version: ${DSSE_VERSION_STR}")

set(DSSE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(DSSE_HEADER_FOLDER "include")
set(DSSE_SOURCE_FOLDER "src")

# some build options
set(CMAKE_FIND_FRAMEWORK LAST)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${DSSE_SOURCE_DIR}/cmake/modules/")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
             
# output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${DSSE_SOURCE_DIR}/bin) # exe
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${DSSE_SOURCE_DIR}/bin) # .dylib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${DSSE_SOURCE_DIR}/lib) # .a
make_directory(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
make_directory(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# configure projects
include(${DSSE_SOURCE_DIR}/cmake/Config.cmake)

# add our projects
add_subdirectory(src)
add_subdirectory(doc)


