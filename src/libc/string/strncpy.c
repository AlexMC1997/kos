#include "string.h"
#include "stdint.h"

//Copies string at src to dest, up to n chars.
void* strncpy(char* dest, char* src, size_t n)
{
    return memcpy(dest, src, n);
}