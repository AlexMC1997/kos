#include "string.h"

//returns length of null terminated string
size_t strlen(const char* s)
{
    size_t len = 0;
    for (; s[len]; len++);
    return len;
}