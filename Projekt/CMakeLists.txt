cmake_minimum_required(VERSION 3.28)
project(
  nlp_platform
  VERSION 1.0.0
  DESCRIPTION "NLP Platform Integration"
  LANGUAGES CXX
  )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "Michał Czyż & Dawid Głąb (c) 2024")
message(STATUS "All rights reserved")

add_executable(nlp src/main.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
# find_package(GTest REQUIRED)

enable_testing()

add_executable(
  hello_test
  test/hello_test.cc
)
target_link_libraries(
  hello_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)
