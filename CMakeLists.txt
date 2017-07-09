# CMake build instructions for Dreamshows engine

# configure cmake
cmake_minimum_required(VERSION 3.1)

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

include_directories(
    ${DSSE_SOURCE_DIR}/include
)

include(cmake_sources.txt)

add_library(Dsse STATIC ${DSSE_HEADERS} ${DSSE_SOURCES})

install(DIRECTORY ${DSSE_SOURCE_DIR}/include
        DESTINATION include)

install(TARGETS Dsse
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

# SpdLog lib
include_directories(${DSSE_SOURCE_DIR}/external/spdlog/include)
install(DIRECTORY ${DSSE_SOURCE_DIR}/external/spdlog/include
        DESTINATION include)
# GLM lib
# include_directories(${DSSE_SOURCE_DIR}/external/glm)
# install(DIRECTORY ${DSSE_SOURCE_DIR}/external/glm
        # DESTINATION include)

# add our projects
add_subdirectory(doc)
add_subdirectory(programs)

