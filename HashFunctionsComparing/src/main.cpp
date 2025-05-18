#include <stdio.h>
#include <stdlib.h>

#include "Tests.hpp"

int main(int argc, char** argv) {
    TestsType* tests_type = (TestsType*)calloc(1, sizeof(TestsType));
    testsTypeCtr(tests_type);

    parseFlags(argc, argv, tests_type);
    switch(tests_type->string_tests) {
        case LENGTH_HASH:
            testStringHashFunction(lengthHash);
            break;
        case SUM_HASH:
            testStringHashFunction(sumHash);
            break;
        case POLYNOMIAL_HASH:
            testStringHashFunction(polynomialHash);
            break;
        case CRC32_HASH:
            testStringHashFunction(crc32Hash);
            break;
        default:
            printf("Unknown string_tests flag: %d\n", tests_type->string_tests);
            break;
    }

}
