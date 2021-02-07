#include "string.h"
#include "stdint.h"

//Copies n bytes from src to dest. 
//Regions must not overlap.
void* memcpy(void* restrict dest, void* restrict src, size_t n)
{
    uint8_t tmp;
    uint8_t* src_t = (uint8_t*)src;
    uint8_t* dest_t = (uint8_t*)dest;
    for (size_t i = 0; i < n; i++) {
        tmp = *src_t++;
        *dest_t++ = tmp;
    }

    return dest;
}