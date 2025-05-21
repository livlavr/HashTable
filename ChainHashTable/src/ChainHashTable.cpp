#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <immintrin.h>

#include "llist.h"
#include "llistDump.h"
#include "StringHash.hpp"
#include "ChainHashTable.hpp"
#include "custom_asserts.h"

static const int CTOR_LINKED_LIST_CAPACITY = 20;
static const int MAX_WORD_LENGTH           = 32;
#ifndef HASH_FUNCTION
    #define HASH_FUNCTION crc32HashIntrinsics;
#endif

#define HASH_FUNCTION_INLINE(key, hash)                               \
    hash = 0xFFFFFFFF;                                                \
                                                                      \
    uint64_t string_key1 = 0;                                         \
    uint64_t string_key2 = 0;                                         \
    uint64_t string_key3 = 0;                                         \
    uint64_t string_key4 = 0;                                         \
                                                                      \
    memcpy(&string_key1, key + 0, 8);                                 \
    memcpy(&string_key2, key + 8, 8);                                 \
    memcpy(&string_key3, key + 16, 8);                                \
    memcpy(&string_key4, key + 24, 8);                                \
                                                                      \
    hash = _mm_crc32_u64(hash, string_key1);                          \
    hash = _mm_crc32_u64(hash, string_key2);                          \
    hash = _mm_crc32_u64(hash, string_key3);                          \
    hash = _mm_crc32_u64(hash, string_key4)

ChainHashTableErrors chainHashTableCtor(ChainHashTable* hash_table, int ctor_capacity) {
    warning(hash_table,        CHAIN_NULL_PTR_ERROR);
    warning(ctor_capacity > 0, CHAIN_CTOR_CAPACITY_ERROR);

    hash_table->capacity     = ctor_capacity;
    hash_table->size         = 0;
    hash_table->hashFunction = HASH_FUNCTION;

    hash_table->buckets = (LinkedList**)calloc(ctor_capacity, sizeof(LinkedList*));
    warning(hash_table->buckets, CHAIN_NULL_PTR_ERROR);

    for(int i = 0; i < ctor_capacity; i++) {
        hash_table->buckets[i] = (LinkedList*)calloc(1, sizeof(LinkedList));
        llistCtor(hash_table->buckets[i], CTOR_LINKED_LIST_CAPACITY);
    }

    return CHAIN_HASH_SUCCESS;
}

__attribute__((target("avx2")))
ChainHashTableErrors chainHashTableInsert(ChainHashTable* hash_table, const char* key) {
    warning(hash_table, CHAIN_NULL_PTR_ERROR);

    if(chainHashTableSearch(hash_table, key) == FOUND) {
        return CHAIN_ALREADY_EXIST_ERROR;
    }

    char* allocated_key = (char*)calloc(MAX_WORD_LENGTH, sizeof(char));
    strncpy(allocated_key, key, MAX_WORD_LENGTH);

    uint64_t hash = 0;
    HASH_FUNCTION_INLINE(key, hash);
    int index = hash % hash_table->capacity;

    Element element = {.key  = allocated_key,
                       .hash = hash};

    llistPushBack(hash_table->buckets[index], &element);

    (hash_table->size)++;

    return CHAIN_HASH_SUCCESS;
}

ChainHashTableErrors chainHashTableRehash(ChainHashTable* hash_table) {
    int new_capacity = hash_table->capacity * 2;
    LinkedList** new_buckets = (LinkedList**)calloc(new_capacity, sizeof(LinkedList*));

    for (int i = 0; i < new_capacity; i++) {
        new_buckets[i] = (LinkedList*)calloc(1, sizeof(LinkedList));
        llistCtor(new_buckets[i], CTOR_LINKED_LIST_CAPACITY);
    }

    for (int i = 0; i < hash_table->capacity; i++) {
        LinkedList* llist = hash_table->buckets[i];
        int index = 0;
        for (int j = 0; j < llist->size; j++) {
            index = llist->next[index];
            char* key     = llist->data[index].key;
            uint64_t hash = llist->data[index].hash;
            Element element = {.key = key, .hash = hash};
            llistPushBack(new_buckets[hash % hash_table->capacity], &element);
        }
    }

    for (int i = 0; i < hash_table->capacity; i++) {
        llistDtor(hash_table->buckets[i]);
        FREE(hash_table->buckets[i]);
    }
    FREE(hash_table->buckets);

    hash_table->buckets  = new_buckets;
    hash_table->capacity = new_capacity;

    return CHAIN_HASH_SUCCESS;
}

float chainHashTableGetLoadFactor(ChainHashTable* hash_table) {
    float size     = (float)hash_table->size;
    float capacity = (float)hash_table->capacity;

    return (size / capacity);
}

__attribute__((target("avx2")))
ChainHashTableSearchStatus chainHashTableSearch(ChainHashTable* hash_table, const char* key) {
    warning(hash_table, NOT_FOUND);

    uint64_t hash = 0;
    HASH_FUNCTION_INLINE(key, hash);
    int bucket_index = hash % hash_table->capacity;
    LinkedList* llist = hash_table->buckets[bucket_index];
    int index = 0;
    for (int i = 0; i < llist->size; i++) {
        index = llist->next[index];
        int cmp_result = 0;

        asm volatile (
            "vmovdqu (%1), %%ymm0           \n\t" // load 32 bytes from ptr1 to ymm0
            "vmovdqu (%2), %%ymm1           \n\t" // load 32 bytes from ptr2 to ymm1
            "vpcmpeqb %%ymm0, %%ymm1, %%ymm0\n\t" // ymm0 = (ymm0 == [ptr2])
            "vpmovmskb %%ymm0, %0           \n\t" //  cmp_result = movemask(ymm0)
            "vzeroupper                     \n\t"
            : "=r"(cmp_result)                    // вывод в любой регистр
            : "r"(llist->data[index].key),        // %1 = ptr1
              "r"(key)                            // %2 = ptr2
            : "ymm0", "ymm1", "memory"            // clobber: ymm0/1, memory
        );

        if (cmp_result == 0xFFFFFFFF) {
            return FOUND;
        }
    }

    return NOT_FOUND;
}

__attribute__((target("avx2")))
ChainHashTableErrors chainHashTableDelete(ChainHashTable* hash_table, const char* key) {
    warning(hash_table, CHAIN_NULL_PTR_ERROR);

    uint64_t hash = 0;
    HASH_FUNCTION_INLINE(key, hash);
    int bucket_index  = hash % hash_table->capacity;
    LinkedList* llist = hash_table->buckets[bucket_index];

    int index = 0;
    for (int i = 0; i < llist->size; i++) {
        index = llist->next[index];
        if (strcmp(llist->data[index].key, key) == 0) {
            llistErase(llist, index);
            (hash_table->size)--;

            break;
        }
    }

    return CHAIN_HASH_SUCCESS;
}

ChainHashTableErrors chainHashTableDtor(ChainHashTable* hash_table) {
    for (int bucket_index = 0; bucket_index < hash_table->capacity; bucket_index++) {
        llistDtor(hash_table->buckets[bucket_index]);
        FREE(hash_table->buckets[bucket_index]);
    }

    FREE(hash_table->buckets);

    return CHAIN_HASH_SUCCESS;
}
