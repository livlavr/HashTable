#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ChainHashTable.hpp"
#include "HashTableBenchmark.hpp"
#include "FileHandler.hpp"
#include "FileHandlerSpecializations.hpp"

int main() {
    ChainHashTable* hash_table = (ChainHashTable*)calloc(1, sizeof(ChainHashTable));
    chainHashTableCtor(hash_table, CTOR_HASH_TABLE_CAPACITY);

    const char*    filename  = "../HashFunctionsComparing/TestsSrc/Tests.txt";
    Buffer<char>*  test_file = (Buffer<char>*)calloc(1, sizeof(Buffer<char>));
    Buffer<char*>* lines     = (Buffer<char*>*)calloc(1, sizeof(Buffer<char*>));

    printf("readFile\n");
    readFile<char>(test_file, filename);

    printf("getLinePointersFromFile\n");
    getLinePointersFromFile(lines, test_file);

    for(int symbol_index = 0; symbol_index < test_file->size; symbol_index++) {
        if(lines->data[0][symbol_index] == '\n') {
            lines->data[0][symbol_index] = '\0';
        }
    }

    printf("fillChainHashTable\n");
    fillChainHashTable(hash_table, lines);

    hashTableSearchTest(hash_table, lines);

    printf("chainHashTableDtor\n");
    chainHashTableDtor(hash_table);
    BufferDtor<char>(test_file);
    BufferDtor<char*>(lines);

    FREE(hash_table);
    FREE(test_file);
    FREE(lines);

    return 0;
}
