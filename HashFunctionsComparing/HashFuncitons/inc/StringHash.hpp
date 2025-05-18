#ifndef STRING_HASH_H
#define STRING_HASH_H

#include <stdint.h>

typedef uint32_t (stringHashFunction) (const char* key, uint32_t hash_table_capacity);

extern uint32_t lengthHash    (const char* key, uint32_t hash_table_capacity);
extern uint32_t sumHash       (const char* key, uint32_t hash_table_capacity);
extern uint32_t polynomialHash(const char* key, uint32_t hash_table_capacity);
extern uint32_t crc32Hash     (const char* key, uint32_t hash_table_capacity);

#endif
