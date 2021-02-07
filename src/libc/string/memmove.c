#include "string.h"
#include "stdint.h"
#include "stdlib.h"

//Copies n bytes from src to dest.
//Regions may overlap.
void* memmove(void* dest, void* src, size_t n)
{
    uint8_t* src_t = (uint8_t*)src;
    uint8_t* dest_t = (uint8_t*)dest;
    int32_t dist = (int32_t)dest - (int32_t)src;
    
    if (!dist)
        return src;

    if (dist > 0 && (size_t)dist < n) {
        for (size_t i = n - 1; (long)i >= 0; i--)
            dest_t[i] = src_t[i];
    } else
        memcpy(dest, src, n);

    return dest;
}