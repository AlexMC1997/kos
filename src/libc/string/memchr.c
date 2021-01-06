#include "string.h"
#include "stdint.h"

//Searches n bytes from pointer str for character c.
//Returns pointer to first occurrence, or NULL if not found.
void* memchr(const void* str, char c, size_t n)
{
    char* str_t = (char*)str;
    for (size_t i = 0; i < n; i++) {
        if (str_t[i] == c)
            return str_t + i;
    }

    return NULL;
}