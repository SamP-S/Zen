message(STATUS "Building zen_core examples")

# core examples
set(CORE_EXAMPLES_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(CORE_EXAMPLES_PRIVATE_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE CORE_EXAMPLES_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp"
)
add_executable(zen_core_example ${CORE_EXAMPLES_SOURCES})
target_include_directories(zen_core_example PRIVATE ${CORE_EXAMPLES_PRIVATE_INCLUDES})
target_include_directories(zen_core_example PUBLIC ${CORE_EXAMPLES_INCLUDES})
target_link_libraries(zen_core_example PUBLIC zen::core)
