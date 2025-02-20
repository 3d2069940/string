cmake_minimum_required(VERSION 3.10)

project(my-string)

find_package(GTest REQUIRED)

add_executable(tests
  tests/main.cpp
  tests/allocator_tests.cpp
  tests/string_tests.cpp

  src/allocator.hpp
  src/string.hpp
)

target_include_directories(tests
  PRIVATE
    src
)

target_link_libraries(tests
  PRIVATE
    ${GTEST_LIBRARIES}
)