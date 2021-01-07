#include <stddef.h>
#include "panic.h"
#ifdef NDEBUG
#define assert(expr) (void)0 
#else
//Tests expr. Panics if false.
#define assert(expr) {\
    if (!(expr)) {\
        panic("Assertion failure.");\
}}
#endif