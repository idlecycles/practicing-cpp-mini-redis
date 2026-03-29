cmake_minimum_required(VERSION 3.20)
project(mini-redis LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(mini-redis
    src/main.cpp
    src/server.cpp
    src/resp_parser.cpp
    src/store.cpp
    src/command_handler.cpp
)

target_include_directories(mini-redis PRIVATE include)
