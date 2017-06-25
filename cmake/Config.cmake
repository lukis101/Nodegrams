
#### Project Configuration

#-----------------------------------------------------------
# User options

option(BUILD_SAMPLE         "Include sample" ON)
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
    set(INSTALL_MISC_DIR resource)
endif()

#-----------------------------------------------------------
# Renderer config

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
