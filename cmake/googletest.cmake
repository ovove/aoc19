# Download and build googletest

include(ExternalProject)

ExternalProject_Add(
  googletest
  PREFIX googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  CMAKE_ARGS "-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER};-DCMAKE_CXX_STANDARD=20"
  INSTALL_COMMAND ""
)

ExternalProject_Get_Property(googletest binary_dir)
ExternalProject_Get_Property(googletest source_dir)

add_library(gtest UNKNOWN IMPORTED)
add_library(gtest_main UNKNOWN IMPORTED)
set_target_properties(gtest PROPERTIES IMPORTED_LOCATION ${binary_dir}/lib/libgtest.a)
#set_target_properties(gtest PROPERTIES INCLUDE_DIRECTORIES ${source_dir}/googletest/include)
set_target_properties(gtest_main PROPERTIES IMPORTED_LOCATION ${binary_dir}/lib/libgtest_main.a)
#set_target_properties(gtest_main PROPERTIES INCLUDE_DIRECTORIES ${source_dir}/googletest/include)
add_dependencies(gtest googletest)
add_dependencies(gtest_main googletest)
include_directories(${source_dir}/googletest/include)

add_library(gmock UNKNOWN IMPORTED)
add_library(gmock_main UNKNOWN IMPORTED)
set_target_properties(gmock PROPERTIES IMPORTED_LOCATION ${binary_dir}/lib/libgmock.a)
#set_target_properties(gmock PROPERTIES INCLUDE_DIRECTORIES ${source_dir}/googlemock/include)
set_target_properties(gmock_main PROPERTIES IMPORTED_LOCATION ${binary_dir}/lib/libgmock_main.a)
#set_target_properties(gmock_main PROPERTIES INCLUDE_DIRECTORIES ${source_dir}/googlemock/include)
add_dependencies(gmock googletest)
add_dependencies(gmock_main googletest)
include_directories(${source_dir}/googlemock/include)

# @todo replace include_directories with some target propery
