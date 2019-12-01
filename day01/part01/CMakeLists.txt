
add_executable(puzzled01p01 puzzle.cc)
target_link_libraries(puzzled01p01 PRIVATE range-v3)

add_executable(testd01p01 puzzle.cc)
target_compile_definitions(testd01p01 PRIVATE DO_UNIT_TEST)
target_link_libraries(testd01p01 PRIVATE GTest::gtest_main)
gtest_discover_tests(testd01p01)
