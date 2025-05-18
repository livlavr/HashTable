#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "llist.h"
#include "ChainHashTable.hpp"
#include "TestingSystem.hpp"

int main() {
    testLoadFactor();
    randomOperationsTest();
    mostlyInsertTest();

    return 0;
}
