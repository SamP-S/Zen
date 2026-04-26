message(STATUS "Building zen_platform demos")

# platform demos
set(PLATFORM_DEMOS_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(PLATFORM_DEMOS_PRIVATE_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE PLATFORM_DEMOS_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp"
)
add_executable(zen_platform_demo ${PLATFORM_DEMOS_SOURCES})
target_include_directories(zen_platform_demo PRIVATE ${PLATFORM_DEMOS_PRIVATE_INCLUDES})
target_include_directories(zen_platform_demo PUBLIC ${PLATFORM_DEMOS_INCLUDES})
target_link_libraries(zen_platform_demo PUBLIC zen::platform)