#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "llist.h"
#include "llistDump.h"
#include "StringHash.hpp"
#include "ChainHashTable.hpp"
#include "custom_asserts.h"

static const int CTOR_LINKED_LIST_CAPACITY = 20;
static const int MAX_WORD_LENGTH           = 32;
#define DEFAULT_HASH_FUNCTION crc32HashIntrinsics;

ChainHashTableErrors chainHashTableCtor(ChainHashTable* hash_table, int ctor_capacity) {
    warning(hash_table,        CHAIN_NULL_PTR_ERROR);
    warning(ctor_capacity > 0, CHAIN_CTOR_CAPACITY_ERROR);

    hash_table->capacity     = ctor_capacity;
    hash_table->size         = 0;
    hash_table->hashFunction = DEFAULT_HASH_FUNCTION;

    hash_table->buckets = (LinkedList**)calloc(ctor_capacity, sizeof(LinkedList*));
    warning(hash_table->buckets, CHAIN_NULL_PTR_ERROR);

    for(int i = 0; i < ctor_capacity; i++) {
        hash_table->buckets[i] = (LinkedList*)calloc(1, sizeof(LinkedList));
        llistCtor(hash_table->buckets[i], CTOR_LINKED_LIST_CAPACITY);
    }

    return CHAIN_HASH_SUCCESS;
}

ChainHashTableErrors chainHashTableInsert(ChainHashTable* hash_table, const char* key) {
    warning(hash_table, CHAIN_NULL_PTR_ERROR);

    if(chainHashTableSearch(hash_table, key) == FOUND) {
        return CHAIN_ALREADY_EXIST_ERROR;
    }

    char* allocated_key = (char*)calloc(MAX_WORD_LENGTH, sizeof(char));
    strncpy(allocated_key, key, MAX_WORD_LENGTH);

    uint64_t hash = hash_table->hashFunction(allocated_key, MAX_WORD_LENGTH);
    int index = hash % hash_table->capacity;

    Element element = {.key  = allocated_key,
                       .hash = hash};
    // printf("<insert: %s>\n",   element.key);
    // printf("<<element.key: %d>>\n", hash_table->hashFunction(element.key, MAX_WORD_LENGTH) % hash_table->capacity);
    // printf("<%s>\n", element.key);
    // printf("<%d>\n", index);
    // fprintf(stderr, "<hash_table->buckets[index] index: %d>\n", index);
    // fprintf(stderr, "<hash_table->buckets[290]->free: %d>\n", hash_table->buckets[290]->free);
    // fprintf(stderr, "<hash_table->buckets[290]->capacity: %d>\n", hash_table->buckets[290]->capacity);
    // fprintf(stderr, "<hash_table->buckets[290]->next: %d>\n",     hash_table->buckets[290]->next[0]);
    // fprintf(stderr, "<hash_table->buckets[290]->prev: %d>\n",     hash_table->buckets[290]->prev[0]);
    // fprintf(stderr, "<hash_table->buckets[290]->size: %d>\n",     hash_table->buckets[290]->size);
    // fprintf(stderr, "element.key: %s>\n", element.key);

    llistPushBack(hash_table->buckets[index], &element);

    // fprintf(stderr, "AFTER PUSH BACK\n");
    // fprintf(stderr, "<hash_table->buckets[index] index: %d>\n", index);
    // fprintf(stderr, "<hash_table->buckets[290]->free: %d>\n", hash_table->buckets[290]->free);
    // fprintf(stderr, "<hash_table->buckets[290]->capacity: %d>\n", hash_table->buckets[290]->capacity);
    // fprintf(stderr, "<hash_table->buckets[290]->next: %d>\n",     hash_table->buckets[290]->next[0]);
    // fprintf(stderr, "<hash_table->buckets[290]->prev: %d>\n",     hash_table->buckets[290]->prev[0]);
    // fprintf(stderr, "<hash_table->buckets[290]->size: %d>\n",     hash_table->buckets[290]->size);
    // fprintf(stderr, "element.key: %s>\n", element.key);

    // printf("<%d>\n", hash_table->buckets[index]->size);

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

ChainHashTableSearchStatus chainHashTableSearch(ChainHashTable* hash_table, const char* key) {
    warning(hash_table, NOT_FOUND);

    int bucket_index = hash_table->hashFunction(key, MAX_WORD_LENGTH) % hash_table->capacity;
    LinkedList* llist = hash_table->buckets[bucket_index];
    int index = 0;
    // printf("bucket_index: %d\n", bucket_index);
    for (int i = 0; i < llist->size; i++) {
        index = llist->next[index];
        // printf("llist->data[index].key: %s\n", llist->data[index].key);
        // printf("key: %s\n", key);
        if (strcmp(llist->data[index].key, key) == 0) {
            // printf("FOUND\n");
            return FOUND;
        }
    }

    return NOT_FOUND;
}

ChainHashTableErrors chainHashTableDelete(ChainHashTable* hash_table, const char* key) {
    warning(hash_table, CHAIN_NULL_PTR_ERROR);

    int bucket_index  = hash_table->hashFunction(key, MAX_WORD_LENGTH) % hash_table->capacity;
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
