
set(PUZZLE_PART 02)
set(PUZZLE_TARGET "puzzled${PUZZLE_DAY}p${PUZZLE_PART}")
set(TEST_TARGET "testd${PUZZLE_DAY}p${PUZZLE_PART}")

add_executable(${PUZZLE_TARGET} puzzle.cc)
target_compile_definitions(${PUZZLE_TARGET} PRIVATE BINARY_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\")
target_link_libraries(${PUZZLE_TARGET} range-v3)

add_executable(${TEST_TARGET} puzzle.cc)
target_compile_definitions(${TEST_TARGET} PRIVATE DO_UNIT_TEST)
target_link_libraries(${TEST_TARGET} PRIVATE GTest::gtest_main)
gtest_discover_tests(${TEST_TARGET})
