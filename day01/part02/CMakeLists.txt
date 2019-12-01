
add_executable(puzzled01p02 puzzle.cc)
target_compile_definitions(puzzled01p02 PRIVATE BINARY_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\")
target_link_libraries(puzzled01p02 range-v3)

add_executable(testd01p02 puzzle.cc)
target_compile_definitions(testd01p02 PRIVATE DO_UNIT_TEST)
target_link_libraries(testd01p02 PRIVATE GTest::gtest_main)
gtest_discover_tests(testd01p02)
