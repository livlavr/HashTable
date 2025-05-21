cmake_minimum_required(VERSION 3.11)

set(CMAKE_C_STANDARD   17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED   True)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ENV{CC}  "gcc")
set(ENV{CXX} "g++")

message(STATUS "C standard ${CMAKE_C_STANDARD}")
message(STATUS "C++ standard ${CMAKE_CXX_STANDARD}")

project(HashTableBenchmark)

add_executable(HashTableBenchmark
    ${CMAKE_CURRENT_SOURCE_DIR}/src/HashTableBenchmark.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

target_include_directories(HashTableBenchmark PUBLIC
    inc
    ${CMAKE_CURRENT_SOURCE_DIR}/TextFileHandler
)

target_link_libraries(HashTableBenchmark PUBLIC
    HashTable
)
