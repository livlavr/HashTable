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

set(COMMON_FLAGS -g -std=c++20 -march=native -mtune=native)
set(DEBUG_FLAGS -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wno-format-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wno-switch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wno-unused-parameter -Wstack-protector -Werror=vla -Wno-write-strings)
set(RELEASE_FLAGS -O3 -std=c++20 -march=native -mtune=native -mavx2)


get_property(CURRENT_CONFIG GLOBAL PROPERTY CONFIG)
if (CURRENT_CONFIG STREQUAL "Default")
    add_compile_options(${COMMON_FLAGS})
endif()
if (CURRENT_CONFIG STREQUAL "Debug")
    add_compile_options(${DEBUG_FLAGS})
endif()
if (CURRENT_CONFIG STREQUAL "Release")
    add_compile_definitions(INTRINSICS_SUPPORTED)
    add_compile_options(${RELEASE_FLAGS})
endif()

message(STATUS "-- Current CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

add_subdirectory(${CMAKE_SOURCE_DIR}/HashFunctions)
add_subdirectory(${CMAKE_SOURCE_DIR}/HashFunctionsComparing)
add_subdirectory(${CMAKE_SOURCE_DIR}/ChainHashTable)
