#include <stdio.h>
#include <stdlib.h>

#include "llist.h"
#include "llistDump.h"
#include "StringHash.hpp"
#include "ChainHashTable.hpp"
#include "custom_asserts.h"

ChainHashTableErrors chainHashTableCtor(ChainHashTable* hash_table, int ctor_capacity) {
    warning(hash_table, CHAIN_NULL_PTR_ERROR);
    warning(ctor_capacity > 0, CHAIN_CTOR_CAPACITY_ERROR);

    hash_table->capacity    = ctor_capacity;
    hash_table->load_factor = 0;
    hash_table->size        = 0;

    hash_table->buckets = (LinkedList**)calloc(ctor_capacity, sizeof(LinkedList*));
    for(int i = 0; i < ctor_capacity; i++) {
        hash_table->buckets[i] = (LinkedList*)calloc(1, sizeof(LinkedList));

        warning(llistCtor(hash_table->buckets[i], CTOR_LINKED_LIST_CAPACITY) == SUCCESS, CHAIN_HASH_ERROR);
    }

    return CHAIN_HASH_SUCCESS;
}

ChainHashTableErrors chainHashTableInsert(ChainHashTable* hash_table, const char* key) {
    warning(hash_table, CHAIN_NULL_PTR_ERROR);

    int index = crc32HashIntrinsics(key, MAX_WORD_LENGTH) % hash_table->capacity;

    warning(llistPushBack(hash_table->buckets[index], key) == LINKED_LIST_SUCCESS, );
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
            uint32_t key = llist->data[index];
            int new_index = mulHash(key, new_capacity);
            llistPushBack(new_buckets[new_index], key);
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

int chainHashTableSearch(ChainHashTable* hash_table, uint32_t key) {
    int bucket_index = mulHash(key, hash_table->capacity);
    LinkedList* llist = hash_table->buckets[bucket_index];
    int index = 0;
    for (int i = 0; i < llist->size; i++) {
        index = llist->next[index];
        if (llist->data[index] == key) {
            return 1;
        }
    }

    return 0;
}

ChainHashTableErrors chainHashTableDelete(ChainHashTable* hash_table, uint32_t key) {
    int bucket_index = mulHash(key, hash_table->capacity);
    LinkedList* llist = hash_table->buckets[bucket_index];

    int index = 0;
    for (int i = 0; i < llist->size; i++) {
        index = llist->next[index];
        if (llist->data[index] == key) {
            llistErase(llist, index);
            (hash_table->size)--;
        }
    }

    return CHAIN_HASH_ERROR;
}

ChainHashTableErrors chainHashTableDtor(ChainHashTable* hash_table) {
    for (int i = 0; i < hash_table->capacity; i++) {
        llistDtor(hash_table->buckets[i]);
        FREE(hash_table->buckets[i]);
    }

    FREE(hash_table->buckets);

    return CHAIN_HASH_SUCCESS;
}
