#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "HashFunctionsBenchmark.hpp"

static const uint64_t HASH_TABLE_CAPACITY = 1000;
static const size_t   WORD_MAX_LENGTH = 32;

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

void testStringHashFunction(stringHashFunction* hash_function) {
    size_t tests_count = 0;
    scanf("%lu", &tests_count);
    uint64_t* result_array = (uint64_t*)calloc(HASH_TABLE_CAPACITY, sizeof(uint64_t));

    char* key_string = (char*)calloc(WORD_MAX_LENGTH, sizeof(char));
    uint64_t hash = 0;

    uint64_t begin = rdtsc();
    for(size_t i = 0; i < tests_count; i++) {
        scanf("%s", key_string);
        hash = hash_function(key_string, WORD_MAX_LENGTH);
        (result_array[hash % HASH_TABLE_CAPACITY])++;
    }
    uint64_t end = rdtsc();

    printf("%lu\n", HASH_TABLE_CAPACITY);
    printf("%lu\n", end - begin);
    for(size_t i = 0; i < HASH_TABLE_CAPACITY; i++) {
        printf("%lu %lu\n", i, result_array[i]);
    }

    FREE(key_string);
    FREE(result_array);
}

void parseFlags(int argc, char** argv, int* tests_type) {
    const char* short_options = "h::";

    if (argc > 3) {
        printf("Only one flag enabled!\n");
        exit(1);
    }

    const struct option long_options[] = {
        {"hash", required_argument, NULL, 'h'},
        {NULL, 0, NULL, 0}
    };

    int rez = 0;

	while((rez = getopt_long(argc, argv, short_options, long_options, NULL)) != -1){
        switch(rez) {
            case 'h':
                if(optarg != NULL) {
                    if(strcmp(optarg, "sumHash") == 0) {
                        *tests_type = SUM_HASH;
                    }
                    else if(strcmp(optarg, "polynomialHash") == 0) {
                        *tests_type = POLYNOMIAL_HASH;
                    }
                    else if(strcmp(optarg, "crc32Hash") == 0) {
                        *tests_type = CRC32_HASH;
                    }
                    else if(strcmp(optarg, "crc32HashOptimized") == 0) {
                        *tests_type = CRC32_HASH_OPTIMIZED;
                    }
                    else if(strcmp(optarg, "crc32HashIntrinsics") == 0) {
                        *tests_type = CRC32_HASH_INTRINSICS;
                    }
                } else {
                    *tests_type = UNDEFINED_HASH_FUNCTION;
                }
                break;
            default:
                break;
        }
    }

}
