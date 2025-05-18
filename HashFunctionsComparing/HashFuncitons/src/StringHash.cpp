#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <nmmintrin.h>

#include "StringHash.hpp"

const uint64_t Polynomial = 0xEDB88320;

uint64_t crc32Hash(const char* data, size_t length) {
    uint64_t crc = 0xFFFFFFFF;
    unsigned char* current = (unsigned char*) data;
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

uint64_t crc32HashOptimized(const char* data, size_t length) {
    uint64_t crc = 0xFFFFFFFF;
    unsigned char* current = (unsigned char*) data;
    while (length--) {
        crc ^= *current++;
        for (uint64_t j = 0; j < 8; j++) {
            crc = (crc >> 1) ^ (-(int)(crc & 1) & Polynomial);
        }
    }

    return ~crc;
}

uint64_t crc32HashIntrinsics(const char* data, size_t length) {
    uint64_t crc = 0xFFFFFFFF;

    uint64_t data_key1 = 0;
    uint64_t data_key2 = 0;
    uint64_t data_key3 = 0;
    uint64_t data_key4 = 0;

    uint64_t data_key1 = memcpy(&data_key1, data + 0, 8);
    uint64_t data_key2 = memcpy(&data_key2, data + 8, 8);
    uint64_t data_key3 = memcpy(&data_key3, data + 16, 8);
    uint64_t data_key4 = memcpy(&data_key4, data + 24, 8);

    crc = _mm_crc32_u64(crc, data_key1);
    crc = _mm_crc32_u64(crc, data_key2);
    crc = _mm_crc32_u64(crc, data_key3);
    crc = _mm_crc32_u64(crc, data_key4);

    return crc;
}

uint64_t sumHash(const char* key) {
    uint64_t sum = 0;
    uint64_t mod = (uint64_t)(1e9 + 7);
    while (*key != '\0') {
        sum += (unsigned char)*key;
        key++;
    }
    return sum % mod;
}

uint64_t polynomialHash(const char* key) {
    const uint64_t base = 31;
    uint64_t mod = (uint64_t)(1e9 + 7);
    uint64_t hash = 0;
    while (*key != '\0') {
        hash = (hash * base + (unsigned char)*key) % hash_table_capacity;
        key++;
    }
    return hash % mod;
}
