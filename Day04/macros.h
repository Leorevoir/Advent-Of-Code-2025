#ifndef AOC_MACROS_H_
#define AOC_MACROS_H_

#include <stdlib.h>

#define ERROR 84
#define SUCCESS 0
#define defer_ptr __attribute__((cleanup(free_ptr)))

typedef unsigned int u32;
typedef signed int i32;

static inline void free_ptr(char **ptr)
{
    if (!ptr || !*ptr)
    {
        return;
    }
    free(*ptr);
}

#endif /* AOC_MACROS_H_ */
