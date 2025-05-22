#ifndef FILE_HANDLER_SPECIALIZATIONS_HPP_
#define FILE_HANDLER_SPECIALIZATIONS_HPP_

template <>
inline FileHandlerError scanFileToBuffer<char>(Buffer<char>* buffer_struct, const char* filename);
template <>
inline FileHandlerError BufferDtor<char> (Buffer<char>* buffer_struct);
template <>
inline FileHandlerError BufferDtor<char*>(Buffer<char*>* buffer_struct);
template <>
inline int CountLines<char>(Buffer<char>* buffer_struct);

template <>
inline FileHandlerError scanFileToBuffer<char>(Buffer<char>* buffer, const char* filename) {
    warning(buffer,      FILE_HANDLER_NULL_PTR_ERROR);
    warning(filename,    FILE_HANDLER_NULL_PTR_ERROR);

    FILE* file = fopen(filename, "r");
    customAssert(file, FILE_HANDLER_OPEN_ERROR);

    size_t fread_status = fread(buffer->data, sizeof(char), (size_t)buffer->size, file);
    customAssert(fread_status > 0, FILE_HANDLER_READ_ERROR);

    fclose(file);

    return FILE_HANDLER_SUCCESS;
}

inline FileHandlerError getLinePointersFromFile(Buffer<char*>* lines, Buffer<char>* text) {
    warning(lines, FILE_HANDLER_NULL_PTR_ERROR);
    warning(text,  FILE_HANDLER_NULL_PTR_ERROR);

    lines->size = CountLines(text);

    lines->data = (char**)calloc((size_t)(lines->size + 1), sizeof(char*));
    warning(lines->data, FILE_HANDLER_ALLOCATION_ERROR);

    int line_index = 1;
    lines->data[0] = text->data;
    for(int index = 0; index < text->size; index++) {
        if(text->data[index] == '\n') {
            lines->data[line_index] = &(text->data[index + 1]);
            line_index++;
        }
    }

    return FILE_HANDLER_SUCCESS;
}


template <>
inline int CountLines<char>(Buffer<char>* buffer) {
    warning(buffer, FILE_HANDLER_NULL_PTR_ERROR);

    int lines_number = 0;
    for(int index = 0; index < buffer->size; index++) {
        if(buffer->data[index] == '\n') {
            lines_number++;
        }
    }
    lines_number++;

    return lines_number;
}

template <>
inline FileHandlerError BufferDtor<char>(Buffer<char>* buffer) {
    warning(buffer, FILE_HANDLER_NULL_PTR_ERROR);

    buffer->size = 0;
    FREE(buffer->data);
    buffer->data = NULL;

    return FILE_HANDLER_SUCCESS;
}

template <>
inline FileHandlerError BufferDtor<char*>(Buffer<char*>* buffer) {
    warning(buffer, FILE_HANDLER_NULL_PTR_ERROR);

    buffer->size = 0;
    FREE(buffer->data);
    buffer->data = NULL;

    return FILE_HANDLER_SUCCESS;
}

#endif
