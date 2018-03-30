# CMake build instructions for Dreamshows engine

# configure cmake
cmake_minimum_required(VERSION 3.6)

project(DssEngine VERSION 0.1 LANGUAGES CXX)
message("Dss engine version: ${PROJECT_VERSION}")

find_package(spdlog CONFIG REQUIRED)
#find_package(Threads REQUIRED)

# Create target
add_library(${PROJECT_NAME} STATIC "")
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# Assign source files
include(Dsse_files.cmake)

# Compiler requirements
target_compile_features(${PROJECT_NAME}
    PUBLIC cxx_std_11
    # PUBLIC cxx_auto_type
    # PRIVATE cxx_variadic_templates
)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

# Link used libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        spdlog::spdlog
)

# Define headers
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>
    PRIVATE
        src
)

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS ${PROJECT_NAME} EXPORT DsseTargets
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR}  # This is for Windows
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
#install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match)
#install(EXPORT DsseTargets
#    FILE DsseTargets.cmake
#    NAMESPACE ${PROJECT_NAME}::
#    DESTINATION share/${PROJECT_NAME}/cmake
#)
# This makes the project importable from the build directory
#export(TARGETS ${PROJECT_NAME} FILE DsseTargets.cmake)

# Tests
# enable_testing()
# add_executable(testlib
#     test/testlib.cpp)
# target_link_libraries(testlib
#     lib)
# add_test(testlib testlib)
