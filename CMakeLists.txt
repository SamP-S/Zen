# Project configuration for zengine
cmake_minimum_required(VERSION 3.22)
project(zen LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD          20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)
set(CMAKE_BUILD_TYPE            Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")

# -----------------------------
# Options
# -----------------------------

# build options
set(BUILD_LEVEL "platform" CACHE STRING "Build level (core, platform, modules, engine, projects)")
set_property(CACHE BUILD_LEVEL PROPERTY STRINGS core platform modules engine projects)

# optional components
include(CTest) # provides BUILD_TESTING option
option(BUILD_DEMOS "Build demo apps" OFF)

# -----------------------------
# Validate BUILD_LEVEL
# -----------------------------

# validate build level
set(_levels core platform modules engine projects)
list(FIND _levels "${BUILD_LEVEL}" _level_index)
if(_level_index EQUAL -1)
    message(FATAL_ERROR "Invalid BUILD_LEVEL='${BUILD_LEVEL}'. Must be one of: ${_levels}")
endif()

# -----------------------------
# Helper function:  
# -----------------------------

# enables a layer if it's <= selected level
function(enable_layer layer out_var)
    set(_levels core platform modules engine projects)

    list(FIND _levels "${layer}" _layer_index)
    list(FIND _levels "${BUILD_LEVEL}" _current_index)

    if(_layer_index EQUAL -1)
        message(FATAL_ERROR "Unknown layer: ${layer}")
    endif()

    if(_layer_index LESS_EQUAL _current_index)
        set(${out_var} ON PARENT_SCOPE)
    else()
        set(${out_var} OFF PARENT_SCOPE)
    endif()
endfunction()

# -----------------------------
# Resolve what to build
# -----------------------------

enable_layer(core     BUILD_CORE)
enable_layer(platform BUILD_PLATFORM)
enable_layer(modules  BUILD_MODULES)
enable_layer(engine   BUILD_ENGINE)
enable_layer(projects BUILD_PROJECTS)

# -----------------------------
# Debug output (optional)
# -----------------------------

message(STATUS "BUILD_LEVEL: ${BUILD_LEVEL}")
message(STATUS "  CORE:     ${BUILD_CORE}")
message(STATUS "  PLATFORM: ${BUILD_PLATFORM}")
message(STATUS "  MODULES:  ${BUILD_MODULES}")
message(STATUS "  ENGINE:   ${BUILD_ENGINE}")
message(STATUS "  PROJECTS: ${BUILD_PROJECTS}")

# git submodule
find_package(Git REQUIRED)
execute_process(
    COMMAND ${GIT_EXECUTABLE}
    submodule update --init --recursive
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

# -----------------------------
# Build layers
# -----------------------------

# zen core
if (BUILD_CORE)
    add_subdirectory(core)
endif()

# zen platform
if (BUILD_PLATFORM)
    add_subdirectory(platform)
endif()

# zen modules
if (BUILD_MODULES)
    add_subdirectory(modules)
endif()

# zen engine
if (BUILD_ENGINE)
    message(FATAL_ERROR "No engine to build yet")
endif()

# zen projects
if (BUILD_PROJECTS)
    message(FATAL_ERROR "No projects to build yet")
endif()

# # optional: demos
# if (BUILD_DEMOS)
#     add_subdirectory(demos)
# endif()

# # optoinal: tests
# if (BUILD_TESTING)
#     add_subdirectory(tests)
# endif()
