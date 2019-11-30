
add_executable(puzzled00p00 puzzle.cc)

add_executable(testd00p00 test.cc)
target_compile_definitions(testd00p00 PRIVATE DO_UNIT_TEST)
target_link_libraries(testd00p00 PRIVATE GTest::gtest_main)
gtest_discover_tests(testd00p00)
