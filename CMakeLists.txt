cmake_minimum_required(VERSION 2.6)

SET(CMAKE_CXX_FLAGS "-std=gnu++11 -ggdb") #Turn on C++11 Support

set(UNIT_TESTS ut_example.cpp)

include_directories(.)
include_directories(./include)

add_library(gtest SHARED IMPORTED)
set_target_properties(gtest PROPERTIES IMPORTED_LOCATION "./lib/libgtest.a")

add_library(gtest_main SHARED IMPORTED)
set_target_properties(gtest_main PROPERTIES IMPORTED_LOCATION "./lib/libgtest_main.a")

add_library(gmock SHARED IMPORTED)
set_target_properties(gmock PROPERTIES IMPORTED_LOCATION "./lib/libgmock.a")

add_library(gmock_main SHARED IMPORTED)
set_target_properties(gmock_main PROPERTIES IMPORTED_LOCATION "./lib/libgmock_main.a")

add_executable(run-unit-test ${UNIT_TESTS})
target_link_libraries(run-unit-test gtest gtest_main gmock gmock_main pthread)