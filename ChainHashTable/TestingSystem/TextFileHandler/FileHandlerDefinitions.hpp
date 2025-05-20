#ifndef BUFFER_DEFINITIONS_H_
#define BUFFER_DEFINITIONS_H_

template <typename T>
struct Buffer {
    T*  data = NULL;
    int size = 0;
};

enum FileHandlerError {
    FILE_HANDLER_SUCCESS          = 0,
    FILE_HANDLER_NULL_PTR_ERROR   = 1,
    FILE_HANDLER_ALLOCATION_ERROR = 1 << 1,
    FILE_HANDLER_STAT_ERROR       = 1 << 2,
    FILE_HANDLER_READ_ERROR       = 1 << 3,
    FILE_HANDLER_OPEN_ERROR       = 1 << 4,
};

template <typename T>
inline FileHandlerError readFile              (Buffer<T>* buffer_struct, const char* filename);
template <typename T>
inline FileHandlerError scanFileToBuffer      (Buffer<T>* buffer_struct, const char* filename);

template <typename T>
inline FileHandlerError BufferDtor       (Buffer<T>* buffer_struct);

template <typename T>
inline int CountLines (Buffer<T>* buffer_struct);

inline FileHandlerError getSizeOfBuffer        (int* size, const char* filename);
inline FileHandlerError getLinePointersFromFile(Buffer<char*>* buffer_struct, Buffer<char>* text);

#endif
