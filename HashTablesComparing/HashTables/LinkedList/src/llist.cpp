#include <stdio.h>
#include <stdlib.h>

#include "llistErrors.h"
#include "color_printf.h"
#include "custom_asserts.h"
#include "llist.h"
#include "llistDump.h"

LlistErrors llistCtor(LinkedList* llist, int capacity) {
    warning(llist, NULL_POINTER_ERROR);
    warning(capacity > 0, VALUE_ERROR);

    int actual_capacity = capacity + 1;
    llist->data = (int*)calloc(capacity, sizeof(int));
    warning(llist->data, ALLOCATION_ERROR);

    llist->next = (int*)calloc(capacity, sizeof(int));
    warning(llist->next, ALLOCATION_ERROR);

    llist->prev = (int*)calloc(capacity, sizeof(int));
    warning(llist->prev, ALLOCATION_ERROR);

    llist->capacity = actual_capacity;
    llist->size     = 0;
    llist->free     = 1;

    for(int i = 0; i < llist->capacity - 1; i++) {
        llist->next[i] = i + 1;
    }
    llist->next[llist->capacity - 1] = 0;

    for(int i = 1; i < llist->capacity; i++) {
        llist->prev[i] = -1;
        llist->data[i] = -1;
    }

    llist->prev[0] = 0;
    llist->next[0] = 0;

    setDumpFile(llist);

    return SUCCESS;
}

LlistErrors llistResize(LinkedList* llist, int new_capacity) {
    warning(llist, NULL_POINTER_ERROR);
    warning(new_capacity > llist->capacity, VALUE_ERROR);

    int old_capacity = llist->capacity;

    int* new_data = (int*)realloc(llist->data, new_capacity * sizeof(int));
    int* new_next = (int*)realloc(llist->next, new_capacity * sizeof(int));
    int* new_prev = (int*)realloc(llist->prev, new_capacity * sizeof(int));

    llist->data = new_data;
    llist->next = new_next;
    llist->prev = new_prev;

    for (int i = old_capacity; i < new_capacity; ++i) {
        llist->data[i] = -1;
        llist->prev[i] = -1;
    }

    for (int i = old_capacity; i < new_capacity - 2; ++i) {
        llist->next[i] = i + 1;
    }

    llist->next[new_capacity - 1] = 0;
    llist->free = old_capacity;

    llist->capacity = new_capacity;

    return SUCCESS;
}


LlistErrors llistPushBack(LinkedList* llist, int element) {
    llistInsertAfter(llist, element, llist->prev[0]);

    return SUCCESS;
}

LlistErrors llistPopBack(LinkedList* llist) {
    warning(llist, NULL_POINTER_ERROR);
    if(llist->size == 0) {
        color_printf(RED_COLOR, BOLD, "ERROR: Linked-List is empty\n");

        warning(llist->size != 0, NULL_POINTER_ERROR);
    }

    llistErase(llist, llist->prev[0]);

    return SUCCESS;
}

LlistErrors llistInsertAfter(LinkedList* llist, int element, int index) {
    if (llist->free == 0) {
        llistResize(llist, llist->capacity * 2);
    }

    if(llist->prev[index] == -1) {
        color_printf(RED_COLOR, BOLD, "ERROR: You trying to insert element after free cell\n");
        warning(llist->prev[index] != -1, INPUT_ERROR);
    }

    //Add element to data
    llist->data[llist->free] = element;

    //Connect index+1 element with first free cell (prev = free)
    llist->prev[llist->next[index]] = llist->free;

    //Change prev of first free cell to index (prev = index)
    llist->prev[llist->free] = index;

    //Change index of first free cell
    llist->free = llist->next[llist->free];

    //Change index "next" of inserted element on next logical cell
    llist->next[llist->prev[llist->next[index]]] = llist->next[index];

    //Change index "next" of element before inserted
    llist->next[index] = llist->prev[llist->next[index]];

    //Size up
    llist->size++;

    return SUCCESS;
}

LlistErrors llistPushFront(LinkedList* llist, int element) {
    warning(llist, NULL_POINTER_ERROR);
    if(llist->free == 0) {
        color_printf(RED_COLOR, BOLD, "ERROR: Linked-List is full\n");

        warning(llist->free != 0, VALUE_ERROR);
    }

    llistInsertAfter(llist, element, 0);

    return SUCCESS;
}

LlistErrors llistErase(LinkedList* llist, int index) {
    warning(llist, NULL_POINTER_ERROR);

    //Poison data value
    llist->data[index] = -1;

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

    return SUCCESS;
}

LlistErrors llistDtor(LinkedList* llist) {
    llist->capacity = 0;
    llist->free     = 0;
    llist->size     = 0;
    free(llist->data);
    free(llist->next);
    free(llist->prev);

    return SUCCESS;
}
