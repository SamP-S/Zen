message(STATUS "Building zen_core examples")

# core demos
set(CORE_DEMOS_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(CORE_DEMOS_PRIVATE_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE CORE_DEMOS_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp"
)
add_executable(zen_core_demo ${CORE_DEMOS_SOURCES})
target_include_directories(zen_core_demo PRIVATE ${CORE_DEMOS_PRIVATE_INCLUDES})
target_include_directories(zen_core_demo PUBLIC ${CORE_DEMOS_INCLUDES})
target_link_libraries(zen_core_demo PUBLIC zen::core)