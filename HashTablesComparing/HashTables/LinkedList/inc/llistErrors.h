#ifndef LLIST_ERRORS_H
#define LLIST_ERRORS_H

enum LlistErrors {
    SUCCESS            = 0,
    INPUT_ERROR        = 1,
    VALUE_ERROR        = 1 << 1,
    PROGRAM_ERROR      = 1 << 2,
    FILE_OPEN_ERROR    = 1 << 3,
    ALLOCATION_ERROR   = 1 << 4,
    NULL_POINTER_ERROR = 1 << 5
};

#endif
