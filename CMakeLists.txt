cmake_minimum_required(VERSION 3.22.1)
project(api)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)


add_executable(api main.cpp
        server.h
        server.cpp
        student.h)

target_link_libraries(api PRIVATE nlohmann_json::nlohmann_json)