#ifndef LLIST_H_
#define LLIST_H_

#include <stdint.h>
#include "llistErrors.h"

#define FREE(ptr) \
    free(ptr);    \
    ptr = NULL

struct Element {
    char* key;
    uint64_t hash;
};

struct LinkedList {
    Element*  data;
    int*      next;
    int*      prev;
    int       size;
    int       capacity;
    int       free;
    char*     dump_file;
};

LlistErrors llistCtor       (LinkedList* llist, int capacity);
LlistErrors llistDtor       (LinkedList* llist);
LlistErrors llistResize     (LinkedList* llist, int new_capacity);
LlistErrors llistPushBack   (LinkedList* llist, Element* element);
LlistErrors llistPushFront  (LinkedList* llist, Element* element);
LlistErrors llistPopBack    (LinkedList* llist);
LlistErrors llistInsertAfter(LinkedList* llist, Element* element, int index);
LlistErrors llistErase      (LinkedList* llist, int index);

#endif
