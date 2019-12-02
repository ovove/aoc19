
add_executable(puzzled02p02 puzzle.cc)
target_compile_definitions(puzzled02p02 PRIVATE BINARY_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\")

add_executable(testd02p02 puzzle.cc)
target_compile_definitions(testd02p02 PRIVATE DO_UNIT_TEST)
target_link_libraries(testd02p02 PRIVATE GTest::gtest_main)
gtest_discover_tests(testd02p02)
