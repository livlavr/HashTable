#ifndef HASH_TABLE_BENCHMARK_HPP
#define HASH_TABLE_BENCHMARK_HPP

#include "FileHandlerDefinitions.hpp"

void hashTableSearchTest(ChainHashTable* hash_table, Buffer<char*>* lines);
void fillChainHashTable(ChainHashTable* hash_table, Buffer<char*>* lines);

#endif
