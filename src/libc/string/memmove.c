#include "string.h"
#include "stdint.h"

//Copies n bytes from src to dest.
//Regions may overlap.
void* __attribute__((optimize("O0"))) 
memmove(void* dest, void* src, size_t n)
{
    uint8_t* src_t = (uint8_t*)src;
    uint8_t* dest_t = (uint8_t*)dest;
    for (size_t i = 0; i < n; i++) {
        *dest_t++ = *src_t++;
    }

    return dest;
}