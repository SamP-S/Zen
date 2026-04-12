message(STATUS "Building zen_platform examples")

# core examples
set(PLATFORM_EXAMPLES_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(PLATFORM_EXAMPLES_PRIVATE_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE PLATFORM_EXAMPLES_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp"
)
add_executable(zen_platform_example ${PLATFORM_EXAMPLES_SOURCES})
target_include_directories(zen_platform_example PRIVATE ${PLATFORM_EXAMPLES_PRIVATE_INCLUDES})
target_include_directories(zen_platform_example PUBLIC ${PLATFORM_EXAMPLES_INCLUDES})
target_link_libraries(zen_platform_example PUBLIC zen::platform)