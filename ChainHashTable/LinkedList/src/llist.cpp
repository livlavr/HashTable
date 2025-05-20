#include <stdio.h>
#include <stdlib.h>

#include "llistErrors.h"
#include "color_printf.h"
#include "custom_asserts.h"
#include "llist.h"
#include "llistDump.h"

LlistErrors llistCtor(LinkedList* llist, int capacity) {
    warning(llist,        LINKED_LIST_NULL_PTR_ERROR);
    warning(capacity > 0, LINKED_LIST_VALUE_ERROR);

    int actual_capacity = capacity + 1;
    llist->data = (Element*)calloc(actual_capacity, sizeof(Element));
    warning(llist->data, LINKED_LIST_ALLOCATION_ERROR);

    llist->next = (int*)calloc(actual_capacity, sizeof(int));
    warning(llist->next, LINKED_LIST_ALLOCATION_ERROR);

    llist->prev = (int*)calloc(actual_capacity, sizeof(int));
    warning(llist->prev, LINKED_LIST_ALLOCATION_ERROR);

    llist->capacity = capacity;
    llist->size     = 0;
    llist->free     = 1;

    for(int i = 0; i < llist->capacity - 1; i++) {
        llist->next[i] = i + 1;
    }
    llist->next[llist->capacity - 1] = 0;

    for(int i = 1; i < llist->capacity; i++) {
        llist->prev[i]      = -1;
        llist->data[i].key  = NULL;
        llist->data[i].hash = 0;
    }

    llist->prev[0] = 0;
    llist->next[0] = 0;

    // setDumpFile(llist);

    return LINKED_LIST_SUCCESS;
}

LlistErrors llistResize(LinkedList* llist, int new_capacity) {
    warning(llist, LINKED_LIST_NULL_PTR_ERROR);
    warning(new_capacity > llist->capacity, LINKED_LIST_VALUE_ERROR);

    int old_capacity = llist->capacity;

    Element* new_data = (Element*)realloc(llist->data, new_capacity * sizeof(Element));
    warning(new_data, LINKED_LIST_ALLOCATION_ERROR);

    int* new_next = (int*)realloc(llist->next, new_capacity * sizeof(int));
    warning(new_next, LINKED_LIST_ALLOCATION_ERROR);

    int* new_prev = (int*)realloc(llist->prev, new_capacity * sizeof(int));
    warning(new_prev, LINKED_LIST_ALLOCATION_ERROR);

    llist->data = new_data;
    llist->next = new_next;
    llist->prev = new_prev;

    for (int i = old_capacity; i < new_capacity; i++) {
        llist->prev[i]      = -1;
        llist->data[i].key  = NULL;
        llist->data[i].hash = 0;
    }

    for (int i = old_capacity; i < new_capacity - 1; i++) {
        llist->next[i] = i + 1;
    }
    llist->next[new_capacity - 1] = 0;

    llist->free = old_capacity;
    llist->capacity = new_capacity;

    return LINKED_LIST_SUCCESS;
}


LlistErrors llistPushBack(LinkedList* llist, Element* element) {
    return llistInsertAfter(llist, element, llist->prev[0]);
}

LlistErrors llistPopBack(LinkedList* llist) {
    warning(llist, LINKED_LIST_NULL_PTR_ERROR);

    if(llist->size == 0) {
        color_printf(RED_COLOR, BOLD, "ERROR: Linked-List is empty\n");
        warning(llist->size != 0, LINKED_LIST_NULL_PTR_ERROR);
    }

    return llistErase(llist, llist->prev[0]);
}

LlistErrors llistInsertAfter(LinkedList* llist, Element* element, int index) {
    warning(llist,   LINKED_LIST_NULL_PTR_ERROR);
    warning(element, LINKED_LIST_NULL_PTR_ERROR);

    if (llist->free == 0) {
        // fprintf(stderr, "llistResize\n");
        llistResize(llist, llist->capacity * 2);
    }

    if(llist->prev[index] == -1) {
        color_printf(RED_COLOR, BOLD, "ERROR: You trying to insert element after free cell\n");
        warning(llist->prev[index] != -1, LINKED_LIST_INPUT_ERROR);
    }
    // fprintf(stderr, "<llist->free1: %d>\n", llist->free);
    // fprintf(stderr, "<llist->capacity: %d>\n", llist->capacity);
    // fprintf(stderr, "<llist->next: %d>\n", llist->next[0]);
    // fprintf(stderr, "<llist->prev: %d>\n", llist->prev[0]);
    // fprintf(stderr, "<llist->size: %d>\n", llist->size);

    //Add element to data
    llist->data[llist->free].key  = element->key;
    llist->data[llist->free].hash = element->hash;

    //Connect index+1 element with first free cell (prev = free)
    llist->prev[llist->next[index]] = llist->free;

    //Change prev of first free cell to index (prev = index)
    llist->prev[llist->free] = index;

    // Change index of first free cell
    // fprintf(stderr, "<llist->free2: %d>\n", llist->free);
    llist->free = llist->next[llist->free];
    // fprintf(stderr, "<llist->free3: %d>\n", llist->free);

    //Change index "next" of inserted element on next logical cell
    llist->next[llist->prev[llist->next[index]]] = llist->next[index];

    //Change index "next" of element before inserted
    llist->next[index] = llist->prev[llist->next[index]];

    //Size up
    llist->size++;

    return LINKED_LIST_SUCCESS;
}

LlistErrors llistPushFront(LinkedList* llist, Element* element) {
    warning(llist, LINKED_LIST_NULL_PTR_ERROR);
    if(llist->free == 0) {
        color_printf(RED_COLOR, BOLD, "ERROR: Linked-List is full\n");
        warning(llist->free != 0, LINKED_LIST_VALUE_ERROR);
    }

    return llistInsertAfter(llist, element, 0);
}

LlistErrors llistErase(LinkedList* llist, int index) {
    warning(llist, LINKED_LIST_NULL_PTR_ERROR);

    //Poison data value
    if(llist->data[index].key) {
        FREE(llist->data[index].key);
        llist->data[index].key  = NULL;
    }
    llist->data[index].hash = 0;

    //Next of prev becomes next of deleted index
    llist->next[llist->prev[index]] = llist->next[index];

    //Prev of next becomes prev of deleted index
    llist->prev[llist->next[index]] = llist->prev[index];

    //Make next of deleted index first free cell (include it to the free-elements chain)
    llist->next[index] = llist->free;

    //Prev value of free element is -1
    llist->prev[index] = -1;

    //Change first free cell on deleted index
    llist->free = index;

    //Size down
    llist->size--;

    return LINKED_LIST_SUCCESS;
}

LlistErrors llistDtor(LinkedList* llist) {
    for(int i = 0; i < llist->capacity; i++) {
        if(llist->data[i].key) {
            // printf("<%s>\n", llist->data[i].key);
            FREE(llist->data[i].key);
        }
    }

    llist->capacity = 0;
    llist->free     = 0;
    llist->size     = 0;

    FREE(llist->data);
    FREE(llist->next);
    FREE(llist->prev);

    return LINKED_LIST_SUCCESS;
}
