#ifndef STRING_HASH_H
#define STRING_HASH_H

#include <stdint.h>

typedef uint64_t (stringHashFunction) (const char* key, size_t length);

uint64_t sumHash            (const char* key, size_t length);
uint64_t polynomialHash     (const char* key, size_t length);
uint64_t crc32Hash          (const char* key, size_t length);
uint64_t crc32HashOptimized (const char* key, size_t length);
uint64_t crc32HashIntrinsics(const char* key, size_t length);

#endif
