#include <stdio.h>
#include <stdlib.h>

#include "ChainHashTable.hpp"

void cleanBuffer() {
    char c = 0;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    ChainHashTable* hash_table = (ChainHashTable*)calloc(1, sizeof(ChainHashTable));
    chainHashTableCtor(hash_table, 1000);

    int n = 0;
    scanf("%d", &n);
    cleanBuffer();
    char     operation = 0;
    char     space     = 0;
    char    string[32]  = "";
    for(size_t i = 0; i < n; i++) {
        scanf("%c %s", &operation, string);
        cleanBuffer();
        switch(operation) {
            case '+':
                chainHashTableInsert(hash_table, string);
                break;
            case '-':
                chainHashTableDelete(hash_table, string);
                break;
            case '?':
                if(chainHashTableSearch(hash_table, string) == FOUND) {
                    printf("YES\n");
                } else {
                    printf("NO\n");
                }
                break;
            default:
                printf("Operation not found!\n");
        }
    }

    chainHashTableDtor(hash_table);
    FREE(hash_table);
}
