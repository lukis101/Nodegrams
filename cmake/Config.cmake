
#### Project Configuration

#-----------------------------------------------------------
# User options

# Windows only
if(WIN32)
    # option(RENDER_DIRECT2D  "Renderer: Direct2D" OFF)   
endif()

# Cross-platform
option(RENDER_OPENGL        "Renderer: OPENGL" OFF)
option(BUILD_TEST           "Include unittests" ON)
option(BUILD_SAMPLE         "Include sample" ON)

# This is for development but can be used by the user.
option(ALLOC_STATS "Track memory allocations" OFF)

#-----------------------------------------------------------
# Configure once options known

set(DSSE_PLATFORM_NAME "Null")   # default/fallback platform

# Set the default build type to release with debug info
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo
        CACHE STRING "Type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
    )
endif()

# TODO: Add an option for choosing the build type (shared or static)
# if(NOT BUILD_SHARED_LIBS)
#     set(BUILD_SHARED_LIBS TRUE
#         CACHE BOOL "TRUE to build DSS engine as a shared library, FALSE to build it as a static library."
#     )
# endif()
set(BUILD_SHARED_LIBS FALSE)

# define install directory for miscelleneous files
if(WIN32 AND NOT UNIX)
    set(INSTALL_MISC_DIR .)
elseif(UNIX)
    set(INSTALL_MISC_DIR share/gwork)
endif()

#-----------------------------------------------------------
# Renderer config
#   - Order alphabetic.

if(RENDER_NULL)
    set(DSSE_RENDER_NAME "Null")
    set(DSSE_RENDER_INCLUDES "")
    set(DSSE_RENDER_LIBRARIES )
endif(RENDER_NULL)

if(RENDER_OPENGL)
    find_package(GLFW REQUIRED)
    if (APPLE)
        set(GLFW_DEPENDENCIES "-framework OpenGL")
    elseif(UNIX)
        set(GLFW_DEPENDENCIES "-lGL")
    elseif(WIN32)
        set(GLFW_DEPENDENCIES "opengl32")
    endif()
    set(DSSE_RENDER_NAME "OpenGL")
    set(DSSE_RENDER_INCLUDES "${GLFW_INCLUDE_DIR}")
    set(DSSE_RENDER_LIBRARIES ${GLFW_LIBRARIES} ${GLFW_DEPENDENCIES})
endif(RENDER_OPENGL)

#-----------------------------------------------------------
# Sanity checks and summary

if(NOT DSSE_INPUT_NAME)
    set(DSSE_INPUT_NAME ${DSSE_RENDER_NAME})
endif()

if(NOT DSSE_RENDER_NAME)
    message(FATAL_ERROR "No renderer was specified. See RENDER_<name> options.")
endif(NOT DSSE_RENDER_NAME)

if(DSSE_RENDER_INCLUDES)
    list(REMOVE_DUPLICATES DSSE_RENDER_INCLUDES)
endif()
if(DSSE_RENDER_LIBRARIES)
    list(REMOVE_DUPLICATES DSSE_RENDER_LIBRARIES)
endif()

message("Using renderer ${DSSE_RENDER_NAME} on platform ${DSSE_PLATFORM_NAME}")
message("${DSSE_RENDER_NAME} includes: ${DSSE_RENDER_INCLUDES}")
message("${DSSE_RENDER_NAME} libs: ${DSSE_RENDER_LIBRARIES}")
