#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ChainHashTable.hpp"
#include "TestingSystem.hpp"
#include "custom_asserts.h"
#include "color_printf.h"
#include "FileHandler.hpp"

void randomOperationsTest() {
//     srand(42);
//
//     for (size_t size = 10000; size <= 1000000; size += 10000) {
//         ChainHashTable* hashTable = (ChainHashTable*)calloc(1, sizeof(ChainHashTable));
//         chainHashTableCtor(hashTable, CTOR_HASH_TABLE_CAPACITY, CTOR_HASH_TABLE_LOAD_FACTOR);
//
//         clock_t start = clock();
//         for (size_t i = 0; i < size; i++) {
//             int operation = rand() % 3;
//             uint32_t key = rand() % 1000000;
//             switch (operation) {
//                 case 0:
//                     chainHashTableInsert(hashTable, key);
//                     break;
//                 case 1:
//                     chainHashTableSearch(hashTable, key);
//                     break;
//                 case 2:
//                     chainHashTableDelete(hashTable, key);
//                     break;
//             }
//         }
//         clock_t end = clock();
//         double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
//
//         printf("%lu %.2f\n", size, time_spent);
//
//         chainHashTableDtor(hashTable);
//     }
}

void fillChainHashTable(ChainHashTable* hash_table, Buffer<char*>* lines) {
    if(!hash_table) {
        color_printf(RED_COLOR, BOLD, "Hash table null pointer");
        return;
    }

    int lines_number = 0;
    sscanf(lines->data[0], "%d", &lines_number);

    char key[32] = "";
    for(int i = 1; i < lines_number; i++) {
        sscanf(lines->data[i], "%32s", key);
        chainHashTableInsert(hash_table, key);
    }
}
