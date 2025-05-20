#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ChainHashTable.hpp"
#include "TestingSystem.hpp"
#include "FileHandler.hpp"
#include "FileHandlerSpecializations.hpp"

int main() {
    ChainHashTable* hash_table = (ChainHashTable*)calloc(1, sizeof(ChainHashTable));
    chainHashTableCtor(hash_table, 1000);

    const char*    filename  = "Tests.txt";
    Buffer<char>*  test_file = (Buffer<char>*)calloc(1, sizeof(Buffer<char>));
    Buffer<char*>* lines     = (Buffer<char*>*)calloc(1, sizeof(Buffer<char*>));

    readFile<char>(test_file, filename);

    getLinePointersFromFile(lines, test_file);

    fillChainHashTable(hash_table, lines);

    chainHashTableDtor(hash_table);
    BufferDtor<char>(test_file);
    BufferDtor<char*>(lines);

    FREE(hash_table);
    FREE(test_file);
    FREE(lines);

    return 0;
}
