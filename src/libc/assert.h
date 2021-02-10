#include <stddef.h>
#ifdef NDEBUG
#define assert(expr) (void)0 
#else

//Tests expr. Panics if false.
#define assert(expr) {\
    if (!(expr)) {\
        if (term_initialized) {\
            tprintf("\nAssert failed.\nSource File: %s\nSource Line: %d\nFunction: %s\n", __FILE__, __LINE__, __func__);\
            asm volatile("hlt");\
        } else {\
            panic("Assertion failure.");\
        }\
}}
#endif