
add_executable(puzzled02p01 puzzle.cc)
target_compile_definitions(puzzled02p01 PRIVATE BINARY_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\")

add_executable(testd02p01 puzzle.cc)
target_compile_definitions(testd02p01 PRIVATE DO_UNIT_TEST)
target_link_libraries(testd02p01 PRIVATE GTest::gtest_main)
gtest_discover_tests(testd02p01)
