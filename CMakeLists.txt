cmake_minimum_required(VERSION 3.15)

#include(CMakePrintSystemInformation)

#set(CMAKE_C_COMPILER /opt/local/bin/gcc)
#set(CMAKE_CXX_COMPILER /opt/local/bin/g++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# CMAKE_BUILD_TYPE={Release|Debug}
add_compile_options(-pipe -Wall -Wextra -pedantic -pthread -march=native
  $<$<CONFIG:Release>:-O3>
  $<$<CONFIG:Debug>:-fsanitize=address> $<$<CONFIG:Debug>:-fsanitize=undefined> $<$<CONFIG:Debug>:-fno-omit-frame-pointer>)
add_link_options(-pipe -pthread -march=native
  $<$<CONFIG:Release>:-O3>
  $<$<CONFIG:Release>:-flto> $<$<CONFIG:Release>:-s>
  $<$<CONFIG:Debug>:-fsanitize=address> $<$<CONFIG:Debug>:-fsanitize=undefined> $<$<CONFIG:Debug>:-fno-omit-frame-pointer>)

#include(ProcessorCount)
#ProcessorCount(NCPU)
#message(STATUS "NCPU=${NCPU}")

project(AdventOfCode19 LANGUAGES CXX)

include(GoogleTest)
enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/googletest.cmake)

# Might use this to fetch puzzle data
#include(ExternalData)

# Add subdirectories below here
add_subdirectory(day00)
