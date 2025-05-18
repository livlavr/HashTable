#include <stdio.h>
#include <stdlib.h>

#include "llist.h"
#include "llistDump.h"
#include "ChainHashTable.hpp"
#include "custom_asserts.h"

uint32_t mulHash(const uint32_t key, uint32_t hash_table_capacity) {
    uint32_t A = 2654435769;
    uint64_t product = key * 2654435769;
    uint64_t integer_part = product >> 32;
    integer_part <<= 32;
    uint32_t hash = (uint32_t)(product - integer_part);

    return hash % hash_table_capacity;
}

ChainHashTableErrors chainHashTableCtor(ChainHashTable* hash_table, int ctor_capacity, float ctor_load_factor) {
    hash_table->capacity    = ctor_capacity;
    hash_table->load_factor = ctor_load_factor;
    hash_table->size        = 0;

    hash_table->buckets = (LinkedList**)calloc(ctor_capacity, sizeof(LinkedList*));
    for(int i = 0; i < ctor_capacity; i++) {
        hash_table->buckets[i] = (LinkedList*)calloc(1, sizeof(LinkedList));

        LlistErrors llist_ctor_return = llistCtor(hash_table->buckets[i], CTOR_LINKED_LIST_CAPACITY);
        warning(llist_ctor_return == SUCCESS, CHAIN_HASH_ERROR);
    }

    return CHAIN_HASH_SUCCESS;
}

ChainHashTableErrors chainHashTableInsert(ChainHashTable* hash_table, uint32_t key) {
    int index = mulHash(key, hash_table->capacity);

    if((hash_table->size / hash_table->capacity * hash_table->buckets[0]->capacity) > hash_table->load_factor) {
        chainHashTableRehash(hash_table);
    }

    llistPushBack(hash_table->buckets[index], key);
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

    hash_table->buckets = new_buckets;
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
