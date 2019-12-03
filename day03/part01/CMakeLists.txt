
add_executable(puzzled03p01 puzzle.cc)
target_compile_definitions(puzzled03p01 PRIVATE BINARY_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\")

add_executable(testd03p01 puzzle.cc)
target_compile_definitions(testd03p01 PRIVATE DO_UNIT_TEST)
target_link_libraries(testd03p01 PRIVATE GTest::gtest_main)
gtest_discover_tests(testd03p01)
