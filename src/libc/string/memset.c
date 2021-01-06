#include "string.h"
#include "stdint.h"

//Sets n bytes at str to c.
void* memset(void* str, uint8_t c, size_t n)
{
    uint8_t* str_t = (uint8_t*)str;
    for (size_t i = 0; i < n; i++) 
        str_t[i] = c;
    return str;
}