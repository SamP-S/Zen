message(STATUS "Building zen_platform")

# external dependencies
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/external/sdl2")

# platform library
set(PLATFORM_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(PLATFORM_PRIVATE_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE PLATFORM_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp"
)
add_library(zen_platform STATIC ${PLATFORM_SOURCES})
target_include_directories(zen_platform PUBLIC ${PLATFORM_INCLUDES})
target_include_directories(zen_platform PRIVATE ${PLATFORM_PRIVATE_INCLUDES})

# link zen_core
target_link_libraries(zen_platform PUBLIC zen::core)

# link SDL2
target_link_libraries(zen_platform PUBLIC SDL2::SDL2)

# alias project to match C++ namespace
add_library(zen::platform ALIAS zen_platform)

# demos
if (BUILD_DEMOS)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/demos")
endif()
