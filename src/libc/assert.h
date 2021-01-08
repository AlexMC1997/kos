#include <stddef.h>
#include "panic.h"
#ifdef NDEBUG
#define assert(expr) (void)0 
#else
//Tests expr. Panics if false.
#define assert(expr) {\
    if (!(expr)) {\
        tprintf("\nAssert failed.\nSource File: %s\nSource Line: %d\nFunction: %s\n", __FILE__, __LINE__, __func__);\
        asm("hlt");\
}}
#endif