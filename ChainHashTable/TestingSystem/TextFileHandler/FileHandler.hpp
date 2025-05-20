#ifndef FILE_HANDLER_HPP_
#define FILE_HANDLER_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "custom_asserts.h"
#include "color_printf.h"
#include "FileHandlerDefinitions.hpp"

template <typename T>
inline FileHandlerError readFile(Buffer<T>* buffer, const char* filename) {
    warning(filename, FILE_HANDLER_NULL_PTR_ERROR);

    FILE* file = fopen(filename, "r");
    warning(file, FILE_HANDLER_OPEN_ERROR);

    getSizeOfBuffer(&(buffer->size), filename);

    buffer->data = (T*)calloc(size_t(buffer->size + 1), sizeof(T));
    warning(buffer->data, FILE_HANDLER_ALLOCATION_ERROR);

    scanFileToBuffer<T>(buffer, filename);

    return FILE_HANDLER_SUCCESS;
}

inline FileHandlerError getSizeOfBuffer(int* size, const char* filename) {
    warning(size,     FILE_HANDLER_NULL_PTR_ERROR);
    warning(filename, FILE_HANDLER_NULL_PTR_ERROR);

    struct stat buffer_information = {};

    int stat_check = stat(filename, &buffer_information);
    warning(stat_check != -1, FILE_HANDLER_STAT_ERROR);

    *size = (int)buffer_information.st_size;

    return FILE_HANDLER_SUCCESS;
}

template <typename T>
inline FileHandlerError scanFileToBuffer(Buffer<T>* buffer, const char* filename) {
    warning(buffer,   FILE_HANDLER_NULL_PTR_ERROR);
    warning(filename, FILE_HANDLER_NULL_PTR_ERROR);

    color_printf(YELLOW_COLOR, BOLD, "Please specialize type for %s | FILE: %s | LINE: %d\n", __func__, __FILE__, __LINE__);

    return FILE_HANDLER_SUCCESS;
}

template <typename T>
inline int CountLines(Buffer<T>* buffer) {
    warning(buffer, FILE_HANDLER_NULL_PTR_ERROR);

    color_printf(YELLOW_COLOR, BOLD, "Please specialize type for %s | FILE: %s | LINE: %d\n", __func__, __FILE__, __LINE__);

    return FILE_HANDLER_SUCCESS;
}

template <typename T>
inline FileHandlerError BufferDtor(Buffer<T>* buffer) {
    warning(buffer, FILE_HANDLER_NULL_PTR_ERROR);

    color_printf(YELLOW_COLOR, BOLD, "Please specialize type for %s | FILE: %s | LINE: %d\n", __func__, __FILE__, __LINE__);

    return FILE_HANDLER_SUCCESS;
}

#endif
