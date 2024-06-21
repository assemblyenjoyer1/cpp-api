cmake_minimum_required(VERSION 3.22.1)
project(api)

# gtest requires at least c++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

# main
add_executable(api
  main.cpp
  server.h
  server.cpp
  student.h
)
target_link_libraries(api PRIVATE nlohmann_json::nlohmann_json)

# tests
add_executable(api_test
  server_test.cpp
  server.h
  server.cpp
  student.h
)

target_link_libraries(api_test PRIVATE nlohmann_json::nlohmann_json GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(api_test)
