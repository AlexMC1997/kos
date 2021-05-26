#ifndef _UTIL_H
#define _UTIL_H

#include "gcc.h"

#define check_type(type, x) ({\ 
    type _dummy;\ 
    typeof(x) _dummy2;\ 
    (void)(&_dummy == &_dummy2)\
    1;\
})

//Aligns val to mod.
#define align(val, mod) (val - (val % mod))

//Generic comparator type. Args may be values or pointers.
//The comparator must return 1 if its first argument is greater,
//0 if they are equal or -1 if the second argument is greater.
typedef int8_t (*comparator_f)(void*, void*);

//Swaps bytes at locations p1 and p2.
static inline gcc_inline void swap8(uint8_t* p1, uint8_t* p2) {
    uint8_t tmp = *p1;
    *p1 = *p2;
    *p2 = tmp; 
}

//Swaps words at locations p1 and p2.
static inline gcc_inline void swap16(uint16_t* p1, uint16_t* p2) {
    uint16_t tmp = *p1;
    *p1 = *p2;
    *p2 = tmp; 
}

//Swaps long words at locations p1 and p2.
static inline gcc_inline void swap32(uint32_t* p1, uint32_t* p2) {
    uint32_t tmp = *p1;
    *p1 = *p2;
    *p2 = tmp; 
}

#endif