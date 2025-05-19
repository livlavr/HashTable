cmake_minimum_required(VERSION 3.11)

set(CMAKE_C_STANDARD   17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED   True)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ENV{CC}  "gcc")
set(ENV{CXX} "g++")

message(STATUS "C standard ${CMAKE_C_STANDARD}")
message(STATUS "C++ standard ${CMAKE_CXX_STANDARD}")

project(LinkedList)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Color-printf)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Custom-asserts)

add_library(LinkedList
    ${CMAKE_CURRENT_SOURCE_DIR}/src/llist.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/llistDump.cpp
)

target_include_directories(LinkedList PUBLIC
    inc
)

target_link_libraries(LinkedList PUBLIC
    CustomAsserts
    ColorPrintf
)

