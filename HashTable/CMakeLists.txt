cmake_minimum_required(VERSION 3.11)

set(CMAKE_C_STANDARD   17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED   True)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ENV{CC}  "gcc")
set(ENV{CXX} "g++")

message(STATUS "C standard ${CMAKE_C_STANDARD}")
message(STATUS "C++ standard ${CMAKE_CXX_STANDARD}")

project(HashTablesTests)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/HashTables)

add_executable(HashTablesTests
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TestingSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

target_include_directories(HashTablesTests PUBLIC
    inc
    ${CMAKE_CURRENT_SOURCE_DIR}/HashTables/LinkedList/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/HashTables/inc
)

target_link_libraries(HashTablesTests PUBLIC
    HashTables
)
