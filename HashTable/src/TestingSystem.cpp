#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "llist.h"
#include "ChainHashTable.hpp"
#include "TestingSystem.hpp"

void testLoadFactor() {
    srand(42);

    float load_factors[] = {0.7, 0.9, 1};
    int num_inserts = 1000000;

    for (int i = 0; i < 3; i++) {
        float test_load_factor = load_factors[i];
        ChainHashTable* hashTable = (ChainHashTable*)calloc(1, sizeof(ChainHashTable));
        chainHashTableCtor(hashTable, CTOR_HASH_TABLE_CAPACITY, test_load_factor);

        clock_t start = clock();
        for (int j = 0; j < num_inserts; j++) {
            fprintf(stderr, "%d\n", j);
            uint32_t key = rand() % 1000000;
            chainHashTableInsert(hashTable, key);
        }
        clock_t end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

        printf("%.1f %.2f\n", test_load_factor, time_spent);

        chainHashTableDtor(hashTable);
    }
}

void randomOperationsTest() {
    srand(42);

    for (size_t size = 10000; size <= 1000000; size += 10000) {
        ChainHashTable* hashTable = (ChainHashTable*)calloc(1, sizeof(ChainHashTable));
        chainHashTableCtor(hashTable, CTOR_HASH_TABLE_CAPACITY, CTOR_HASH_TABLE_LOAD_FACTOR);

        clock_t start = clock();
        for (size_t i = 0; i < size; i++) {
            int operation = rand() % 3;
            uint32_t key = rand() % 1000000;
            switch (operation) {
                case 0:
                    chainHashTableInsert(hashTable, key);
                    break;
                case 1:
                    chainHashTableSearch(hashTable, key);
                    break;
                case 2:
                    chainHashTableDelete(hashTable, key);
                    break;
            }
        }
        clock_t end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

        printf("%lu %.2f\n", size, time_spent);

        chainHashTableDtor(hashTable);
    }
}

void mostlyInsertTest() {
    srand(42);

    for (size_t size = 10000; size <= 1000000; size += 10000) {
        ChainHashTable* hashTable = (ChainHashTable*)calloc(1, sizeof(ChainHashTable));
        chainHashTableCtor(hashTable, CTOR_HASH_TABLE_CAPACITY, CTOR_HASH_TABLE_LOAD_FACTOR);

        clock_t start = clock();
        for (size_t i = 0; i < size; i++) {
            uint32_t random_value = rand() % 2;
            uint32_t key = rand() % 1000000;
            if (random_value == 0) {
                chainHashTableInsert(hashTable, key);
            } else {
                random_value = rand() % 2;
                if(random_value == 0) {
                    chainHashTableSearch(hashTable, key);
                } else {
                    chainHashTableDelete(hashTable, key);
                }
            }
        }
        clock_t end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

        printf("%lu %.2f\n", size, time_spent);

        chainHashTableDtor(hashTable);
    }
}
