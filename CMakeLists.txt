cmake_minimum_required(VERSION 3.15)

#include(CMakePrintSystemInformation)

#set(CMAKE_C_COMPILER /opt/local/bin/gcc)
#set(CMAKE_CXX_COMPILER /opt/local/bin/g++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# CMAKE_BUILD_TYPE={Release|Debug}
add_compile_options(-pipe -Wall -Wextra -pedantic -pthread -march=native
  $<$<CONFIG:Release>:-O3>
  $<$<CONFIG:Debug>:-fsanitize=address> $<$<CONFIG:Debug>:-fsanitize=undefined> $<$<CONFIG:Debug>:-fno-omit-frame-pointer>)
add_link_options(-pipe -pthread -march=native
  $<$<CONFIG:Release>:-O3>
  $<$<CONFIG:Release>:-flto>
  $<$<CONFIG:Debug>:-fsanitize=address> $<$<CONFIG:Debug>:-fsanitize=undefined> $<$<CONFIG:Debug>:-fno-omit-frame-pointer>)

#include(ProcessorCount)
#ProcessorCount(NCPU)
#message(STATUS "NCPU=${NCPU}")

include(cmake/HunterGate.cmake)
HunterGate(
  URL "https://github.com/cpp-pm/hunter/archive/v0.23.233.tar.gz"
  SHA1 "27387cd4ab6bbf7f1e7c998fe7ad2f7ec5b12930"
)
include(GoogleTest)
#include(FetchContent)
# Might use this to fetch puzzle data
#include(ExternalData)

project(AdventOfCode19 LANGUAGES CXX)

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)
hunter_add_package(range-v3)
find_package(range-v3 CONFIG REQUIRED)

enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add subdirectories below here
add_subdirectory(day01)
add_subdirectory(day02)
add_subdirectory(day03)
add_subdirectory(day04)
add_subdirectory(day05)
add_subdirectory(day06)
