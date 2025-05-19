#ifndef CHAIN_HASH_TABLE_HPP
#define CHAIN_HASH_TABLE_HPP

#include <cstdint>

#define FREE(ptr) \
    free(ptr);    \
    ptr = NULL

struct ChainHashTable {
    LinkedList** buckets = NULL;
    int   capacity       = 0;
    int   size           = 0;
    float load_factor    = 0;
};

enum ChainHashTableErrors {
    CHAIN_HASH_SUCCESS        = 0,
    CHAIN_HASH_ERROR          = 1 << 0,
    CHAIN_NULL_PTR_ERROR      = 1 << 1,
    CHAIN_CTOR_CAPACITY_ERROR = 1 << 2,
    CHAIN_INSERT_ERROR        = 1 << 3,
};

static const int   CTOR_LINKED_LIST_CAPACITY   = 10000;
static const int   CTOR_HASH_TABLE_CAPACITY    = 10000;
static const int   MAX_WORD_LENGTH             = 32;

ChainHashTableErrors chainHashTableCtor  (ChainHashTable* hash_table, int ctor_capacity, float ctor_load_factor);
ChainHashTableErrors chainHashTableDtor  (ChainHashTable* hash_table);
ChainHashTableErrors chainHashTableInsert(ChainHashTable* hash_table, uint32_t key);
ChainHashTableErrors chainHashTableDelete(ChainHashTable* hash_table, uint32_t key);
ChainHashTableErrors chainHashTableRehash(ChainHashTable* hash_table);
int                  chainHashTableSearch(ChainHashTable* hash_table, uint32_t key);

#endif
