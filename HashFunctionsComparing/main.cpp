#include <stdio.h>
#include <stdlib.h>

#include "HashFunctionTest.hpp"

int main(int argc, char** argv) {
    int tests_type = UNDEFINED_HASH_FUNCTION;

    parseFlags(argc, argv, &tests_type);
    switch(tests_type) {
        case SUM_HASH:
            testStringHashFunction(sumHash);
            break;
        case POLYNOMIAL_HASH:
            testStringHashFunction(polynomialHash);
            break;
        case CRC32_HASH:
            testStringHashFunction(crc32Hash);
            break;
        case CRC32_HASH_OPTIMIZED:
            testStringHashFunction(crc32HashOptimized);
            break;
        // case CRC32_HASH_INTRINSICS:
        //     testStringHashFunction(crc32HashIntrinsics);
            // break;
        default:
            printf("Unknown string_tests flag: %d\n", tests_type);
            break;
    }

}
