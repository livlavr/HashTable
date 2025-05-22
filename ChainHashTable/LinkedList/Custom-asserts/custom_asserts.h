#ifndef CUSTOM_ASSERTS_H_
#define CUSTOM_ASSERTS_H_

#include "Color-printf/color_printf.h"

#ifndef NASSERTS

    #define warning(condition, message) do                                                      \
    {                                                                                           \
        if (!(condition))                                                                       \
        {                                                                                       \
            color_printf(YELLOW_COLOR, BOLD, "ERROR %s : %s, file: %s, function: %s, line: %d\n",\
                        #condition, #message, __FILE__, __FUNCTION__, __LINE__);                \
            printf("\n");                                                                       \
            return message;                                                                     \
        }                                                                                       \
    } while(0)

    #define customAssert(condition, message) do                                                   \
    {                                                                                             \
        if (!(condition))                                                                         \
        {                                                                                         \
            color_printf(RED_COLOR, BOLD, "ERROR %s : %s, file: %s, function: %s, line: %d\n", \
                         #condition, #message, __FILE__, __FUNCTION__, __LINE__);                 \
            printf("\n");                                                                         \
            exit(1);                                                                              \
        }                                                                                         \
    } while(0)

#else

    #define customAssert(condition, message)

    #define warning(condition, message)

#endif
#endif
