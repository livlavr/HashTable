#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ChainHashTable.hpp"
#include "TestingSystem.hpp"
#include "custom_asserts.h"
#include "color_printf.h"
#include "FileHandler.hpp"

static const int NUMBER_OF_TESTS = 100;
static const int NUMBER_OF_WARMUP_TESTS = 100;

static inline uint64_t rdtsc() {
    unsigned int lo, hi;
    __asm__ __volatile__ (
        "cpuid\n\t"
        "rdtsc\n\t"
        : "=a"(lo), "=d"(hi)
        : "a"(0)
        : "%ebx", "%ecx");
    return ((uint64_t)hi << 32) | lo;
}

void hashTableSearchTest(ChainHashTable* hash_table, Buffer<char*>* lines) {
    int lines_number = lines->size;
    char* keys = (char*)calloc(lines_number, sizeof(char)*32);
    for(int word_index = 1; word_index < lines_number; word_index++) {
        strncpy(&(keys[word_index * 32]), lines->data[word_index], 32);
    }

    color_printf(GREEN_COLOR, BOLD, "BEGIN WARMUP\n");
    //Warmup
    for(int test_index = 1; test_index < NUMBER_OF_WARMUP_TESTS; test_index++) {
        for(int word_index = 1; word_index < lines_number; word_index++) {
            // printf("%d/%d\r", test_index, lines_number);
            // printf("<search: %s>\n",     &(keys[word_index * 32]));
            // printf("<<%lu>>\n",   hash_table->hashFunction(&(keys[word_index * 32]), 32) % hash_table->capacity);
            chainHashTableSearch(hash_table, &(keys[word_index * 32]));
        }
    }

    color_printf(GREEN_COLOR, BOLD, "BEGIN TESTS\n");
    //Tests
    uint64_t begin = rdtsc();
    for(int test_index = 1; test_index < NUMBER_OF_TESTS; test_index++) {
        for(int word_index = 1; word_index < lines_number; word_index++) {
            // printf("%d/%d\r", test_index, lines_number);
            chainHashTableSearch(hash_table, &(keys[word_index * 32]));
        }
    }
    uint64_t end = rdtsc();
    uint64_t total = end - begin;

    color_printf(GREEN_COLOR, BOLD, "TIME RESULT: %lu\n", total);
    color_printf(GREEN_COLOR, BOLD, "TIME RESULT (avg for element): %.2f\n", (float)total/NUMBER_OF_TESTS/CTOR_HASH_TABLE_CAPACITY);

    FREE(keys);
}

void fillChainHashTable(ChainHashTable* hash_table, Buffer<char*>* lines) {
    int lines_number = lines->size;
    for(int i = 1; i < lines_number; i++) {
        chainHashTableInsert(hash_table, lines->data[i]);
    }
}
