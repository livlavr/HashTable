cmake_minimum_required(VERSION 3.11)

set(CMAKE_C_STANDARD   17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED   True)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ENV{CC}  "gcc")
set(ENV{CXX} "g++")

message(STATUS "C standard ${CMAKE_C_STANDARD}")
message(STATUS "C++ standard ${CMAKE_CXX_STANDARD}")

project(HashFunctionsComparing)

add_compile_options(
    "$<$<COMPILE_LANGUAGE:CXX>:-O3;-DNDEBUG;-std=c++20;-march=native>"
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/TestingSystem)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/HashFuncitons)

add_executable(HashFunctionsComparing
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_link_libraries(HashFunctionsComparing PUBLIC
    Tests
)

