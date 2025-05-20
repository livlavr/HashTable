cmake_minimum_required(VERSION 3.11)

#################################HashTable########################################

set(CMAKE_C_STANDARD   17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED   True)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ENV{CC}  "gcc")
set(ENV{CXX} "g++")

message(STATUS "C standard ${CMAKE_C_STANDARD}")
message(STATUS "C++ standard ${CMAKE_CXX_STANDARD}")

set(DEBUG_FLAGS -ggdb3 -O0 -Wall -Wextra -Weffc++ -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wno-format-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wnon-virtual-dtor -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=2 -Wsuggest-override -Wno-switch-enum -Wundef -Wunreachable-code -Wunused -Wvariadic-macros -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wno-unused-parameter -Wstack-protector -fsized-deallocation -fstack-protector -fstrict-overflow -fPIC -fno-omit-frame-pointer -fPIE -Werror=vla -Wno-write-strings)
set(RELEASE_FLAGS -O3 -std=c++20 -march=native -mtune=native -masm=intel)

project(HashTable)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/LinkedList)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/HashTableBenchmark)

add_library(HashTable
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ChainHashTable.cpp
)

target_compile_options(HashTable PRIVATE
    $<$<CONFIG:Debug>:${DEBUG_FLAGS}>
    $<$<CONFIG:Release>:${RELEASE_FLAGS}>
)

target_include_directories(HashTable PUBLIC
    LinkedList/inc
    inc
)

target_link_libraries(HashTable PUBLIC
    LinkedList
    HashFunctions
)

############################HashTableUnitTest###################################

add_executable(HashTableUnitTest
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

# target_compile_options(HashTableUnitTest PRIVATE
#     $<$<CONFIG:Debug>:${DEBUG_FLAGS}>
#     $<$<CONFIG:Release>:${RELEASE_FLAGS}>
# )

target_include_directories(HashTable PUBLIC
    LinkedList/inc
    inc
)

target_link_libraries(HashTableUnitTest
    HashTable
)
