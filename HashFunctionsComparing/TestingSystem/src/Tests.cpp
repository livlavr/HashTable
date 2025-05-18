#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "Tests.hpp"
#include "UintHash.hpp"
#include "FloatHash.hpp"

static const uint32_t HASH_TABLE_CAPACITY = 1000;
static const int YES = 1;
static const int NO  = 0;

void testStringHashFunction(stringHashFunction* hash_function) {
    size_t tests_count = 0;
    scanf("%lu", &tests_count);

    uint32_t* result_array = (uint32_t*)calloc(HASH_TABLE_CAPACITY, sizeof(uint32_t));

    char* key_string = (char*)calloc(21, sizeof(char));
    uint32_t hash = 0;
    for(size_t i = 0; i < tests_count; i++) {
        scanf("%s", key_string);
        hash = hash_function(key_string, HASH_TABLE_CAPACITY);
        (result_array[hash])++;
    }

    for(size_t i = 0; i < HASH_TABLE_CAPACITY; i++) {
        printf("%lu %u\n", i, result_array[i]);
    }

    FREE(key_string);
    FREE(result_array);
}

void parseFlags(int argc, char** argv, TestsType* tests_type) {
    const char* short_options = "s::";

    if (argc > 3) {
        printf("Only one flag enabled!\n");
        exit(1);
    }

    const struct option long_options[] = {
        {"string", required_argument, NULL, 's'},
        {NULL, 0, NULL, 0}
    };

    int rez = 0;

	while((rez = getopt_long(argc, argv, short_options, long_options, NULL)) != -1){
        switch(rez) {
            case 's':
                if(optarg != NULL) {
                    if(strcmp(optarg, "lengthHash") == 0) {
                        tests_type->string_tests = LENGTH_HASH;
                    }
                    else if(strcmp(optarg, "sumHash") == 0) {
                        tests_type->string_tests = SUM_HASH;
                    }
                    else if(strcmp(optarg, "polynomialHash") == 0) {
                        tests_type->string_tests = POLYNOMIAL_HASH;
                    }
                    else if(strcmp(optarg, "crc32Hash") == 0) {
                        tests_type->string_tests = CRC32_HASH;
                    }
                } else {
                    tests_type->string_tests = NO;
                }
                break;
            default:
                break;
        }
    }

}

void testsTypeCtr(TestsType* tests_type) {
    tests_type->uint_tests   = NO;
    tests_type->float_tests  = NO;
    tests_type->string_tests = NO;
}
