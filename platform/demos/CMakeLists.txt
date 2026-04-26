message(STATUS "Building zen_platform demos")

# platform demos
set(PLATFORM_DEMOS_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(PLATFORM_DEMOS_PRIVATE_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE PLATFORM_DEMOS_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp"
)
add_executable(zen_platform_demos ${PLATFORM_DEMOS_SOURCES})
target_include_directories(zen_platform_demos PRIVATE ${PLATFORM_DEMOS_PRIVATE_INCLUDES})
target_include_directories(zen_platform_demos PUBLIC ${PLATFORM_DEMOS_INCLUDES})
target_link_libraries(zen_platform_demos PUBLIC zen::platform)