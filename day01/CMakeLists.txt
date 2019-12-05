
set(PUZZLE_DAY 01)

add_subdirectory(part01)
add_subdirectory(part02)

file(COPY input DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
