cmake_minimum_required(VERSION 3.11)

set(CMAKE_C_STANDARD   17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED   True)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ENV{CC}  "gcc")
set(ENV{CXX} "g++")

message(STATUS "C standard ${CMAKE_C_STANDARD}")
message(STATUS "C++ standard ${CMAKE_CXX_STANDARD}")

project(HashTable)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++20 -march=native -mtune=native -masm=intel")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++20 -march=native -flto=auto -fno-omit-frame-pointer -rdynamic")

add_subdirectory(${CMAKE_SOURCE_DIR}/HashFunctions)
add_subdirectory(${CMAKE_SOURCE_DIR}/HashFunctionsComparing)
add_subdirectory(${CMAKE_SOURCE_DIR}/ChainHashTable)
