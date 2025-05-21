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

project(HashTable)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/LinkedList)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/HashTableBenchmark)

add_library(HashTable
${CMAKE_CURRENT_SOURCE_DIR}/src/ChainHashTable.cpp
)

if(DEFINED DEFAULT_HASH_FUNCTION)
    target_compile_definitions(HashTable PRIVATE DEFAULT_HASH_FUNCTION=${DEFAULT_HASH_FUNCTION})
else()
    target_compile_definitions(HashTable PRIVATE DEFAULT_HASH_FUNCTION=crc32HashIntrinsics)
endif()

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

target_include_directories(HashTable PUBLIC
    LinkedList/inc
    inc
)

target_link_libraries(HashTableUnitTest
    HashTable
)
