#ifndef CHAIN_HASH_TABLE_HPP
#define CHAIN_HASH_TABLE_HPP

#include <cstdint>
#include "StringHash.hpp"
#include "llist.h"

#define FREE(ptr) \
    free(ptr);    \
    ptr = NULL

struct ChainHashTable {
    LinkedList** buckets = NULL;
    int   capacity       = 0;
    int   size           = 0;
    stringHashFunction* hashFunction = {};
};

enum ChainHashTableSearchStatus {
    FOUND     = 1,
    NOT_FOUND = 0
};

enum ChainHashTableErrors {
    CHAIN_HASH_SUCCESS        = 0,
    CHAIN_HASH_ERROR          = 1 << 0,
    CHAIN_NULL_PTR_ERROR      = 1 << 1,
    CHAIN_CTOR_CAPACITY_ERROR = 1 << 2,
    CHAIN_INSERT_ERROR        = 1 << 3,
    CHAIN_REHASH_ERROR        = 1 << 4,
    CHAIN_DELETE_ERROR        = 1 << 5,
    CHAIN_ALREADY_EXIST_ERROR = 1 << 6,
};

static const int CTOR_HASH_TABLE_CAPACITY = 1000;

ChainHashTableErrors       chainHashTableCtor  (ChainHashTable* hash_table, int ctor_capacity);
ChainHashTableErrors       chainHashTableDtor  (ChainHashTable* hash_table);
ChainHashTableErrors       chainHashTableInsert(ChainHashTable* hash_table, const char* key);
ChainHashTableErrors       chainHashTableDelete(ChainHashTable* hash_table, const char* key);
ChainHashTableErrors       chainHashTableRehash(ChainHashTable* hash_table);
ChainHashTableSearchStatus chainHashTableSearch(ChainHashTable* hash_table, const char* key);

#endif
