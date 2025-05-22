#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <string.h>
#include <nmmintrin.h>

#include "StringHash.hpp"
#include "custom_asserts.h"

#define INTRINSICS_SUPPORTED

static const uint64_t Polynomial = 0xEDB88320;
static const uint64_t ErrorHashReturnValue = 0xFFFFFFFF;

uint64_t crc32Hash(const char* key, size_t length) {
    warning(key, ErrorHashReturnValue);

    uint64_t crc = 0xFFFFFFFF;
    unsigned char* current = (unsigned char*) key;
    while (length--) {
        crc ^= *current++;
        for (uint64_t j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ Polynomial;
            } else {
                crc =  crc >> 1;
            }
        }
    }

    return ~crc;
}

uint64_t crc32HashOptimized(const char* key, size_t length) {
    warning(key, ErrorHashReturnValue);

    uint64_t crc = 0xFFFFFFFF;
    unsigned char* current = (unsigned char*) key;
    while (length--) {
        crc ^= *current++;
        for (uint64_t j = 0; j < 8; j++) {
            crc = (crc >> 1) ^ (-(int)(crc & 1) & Polynomial);
        }
    }

    return ~crc;
}

#ifdef INTRINSICS_SUPPORTED
    #define CRC32INTRINSICS()                                                 \
        __attribute__((target("avx2")))                                       \
        uint64_t crc32HashIntrinsics(const char* key, size_t length) {        \
            warning(key, ErrorHashReturnValue);                               \
                                                                              \
            uint64_t crc = 0xFFFFFFFF;                                        \
                                                                              \
            uint64_t string_key1 = 0;                                         \
            uint64_t string_key2 = 0;                                         \
            uint64_t string_key3 = 0;                                         \
            uint64_t string_key4 = 0;                                         \
                                                                              \
            crc = _mm_crc32_u64(crc, *((uint64_t*)key + 0));                  \
            crc = _mm_crc32_u64(crc, *((uint64_t*)key + 8));                  \
            crc = _mm_crc32_u64(crc, *((uint64_t*)key + 16));                 \
            crc = _mm_crc32_u64(crc, *((uint64_t*)key + 24));                 \
                                                                              \
            return crc;                                                       \
        }
#else
    #define CRC32INTRINSICS()                                                 \
        uint64_t crc32HashIntrinsics(const char* key, size_t length) {        \
            customAssert(false, "Please change CMAKE_BUILD_TYPE to Release"); \
                                                                              \
            return 0;                                                         \
        }
#endif

CRC32INTRINSICS()
#undef CRC32INTRINSICS
#undef INTRINSICS_SUPPORTED

uint64_t sumHash(const char* key, size_t length) {
    warning(key, ErrorHashReturnValue);

    uint64_t sum = 0;
    uint64_t mod = (uint64_t)(1e9 + 7);
    while (*key != '\0') {
        sum += (unsigned char)*key;
        key++;
    }
    return sum % mod;
}

uint64_t polynomialHash(const char* key, size_t length) {
    warning(key, ErrorHashReturnValue);

    const uint64_t base = 255;
    uint64_t mod = (uint64_t)(1e9 + 7);
    uint64_t hash = 0;
    while (*key != '\0') {
        hash = (hash * base + (unsigned char)(*key)) % mod;
        key++;
    }

    return hash;
}
