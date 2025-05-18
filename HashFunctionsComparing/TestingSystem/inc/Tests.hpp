#ifndef TESTS_HPP
#define TESTS_HPP

#include "UintHash.hpp"
#include "FloatHash.hpp"
#include "StringHash.hpp"

static const int REMINDER_HASH = 1;
static const int MUR_MUR_HASH  = 2;
static const int MUL_HASH      = 3;

static const int FLOAT_TO_INT_HASH       = 1;
static const int MANTISSA_HASH           = 2;
static const int EXP_HASH                = 3;
static const int EXP_TIMES_MANTISSA_HASH = 4;

static const int LENGTH_HASH     = 1;
static const int SUM_HASH        = 2;
static const int POLYNOMIAL_HASH = 3;
static const int CRC32_HASH      = 4;

struct TestsType {
    int uint_tests   = 0;
    int float_tests  = 0;
    int string_tests = 0;
};

#define FREE(ptr) \
    free(ptr);    \
    ptr = NULL

void testUintHashFunction  (uintHashFunction*   hash_function);
void testFloatHashFunction (floatHashFunction*  hash_function);
void testStringHashFunction(stringHashFunction* hash_function);
void testsTypeCtr(TestsType* tests_type);
void parseFlags  (int argc, char** argv, TestsType* tests_type);

#endif
