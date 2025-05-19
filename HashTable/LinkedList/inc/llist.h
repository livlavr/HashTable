#ifndef LLIST_H_
#define LLIST_H_

#include "llistErrors.h"

struct LinkedList {
    int*  data           = NULL;
    int*  next           = NULL;
    int*  prev           = NULL;
    int   size           = 0;
    int   capacity       = 0;
    int   free           = 0;
    char* dump_file      = NULL;
};

LlistErrors llistCtor       (LinkedList* llist, int capacity);
LlistErrors llistDtor       (LinkedList* llist);
LlistErrors llistResize     (LinkedList* llist, int new_capacity);
LlistErrors llistPushBack   (LinkedList* llist, int element);
LlistErrors llistPushFront  (LinkedList* llist, int element);
LlistErrors llistPopBack    (LinkedList* llist);
LlistErrors llistInsertAfter(LinkedList* llist, int element, int index);
LlistErrors llistErase      (LinkedList* llist, int index);

#endif
