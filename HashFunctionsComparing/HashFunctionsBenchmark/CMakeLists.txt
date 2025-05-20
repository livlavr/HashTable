cmake_minimum_required(VERSION 3.11)

set(CMAKE_C_STANDARD   17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED   True)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ENV{CC}  "gcc")
set(ENV{CXX} "g++")

message(STATUS "C standard ${CMAKE_C_STANDARD}")
message(STATUS "C++ standard ${CMAKE_CXX_STANDARD}")

project(HashFunctionsBenchmark)

add_library(HashFunctionsBenchmark
    ${CMAKE_CURRENT_SOURCE_DIR}/src/HashFunctionsBenchmark.cpp
)

target_include_directories(HashFunctionsBenchmark PUBLIC
    inc
)

target_link_libraries(HashFunctionsBenchmark PUBLIC
    HashFunctions
)

