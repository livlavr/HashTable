#ifndef HASH_FUNCTION_TEST_HPP
#define HASH_FUNCTION_TEST_HPP

#include "StringHash.hpp"

static const int UNDEFINED_HASH_FUNCTION = 0;
static const int SUM_HASH                = 1;
static const int POLYNOMIAL_HASH         = 2;
static const int CRC32_HASH              = 3;
static const int CRC32_HASH_OPTIMIZED    = 4;
static const int CRC32_HASH_INTRINSICS   = 5;

struct TestsType {
    int uint_tests   = 0;
    int float_tests  = 0;
    int string_tests = 0;
};

#define FREE(ptr) \
    free(ptr);    \
    ptr = NULL

void testStringHashFunction(stringHashFunction* hash_function);
void parseFlags(int argc, char** argv, int* tests_type);

#endif
