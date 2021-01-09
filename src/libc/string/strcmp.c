#include "string.h"
#include <stddef.h>
#include "stdint.h"

//Compares null-terminated string str1 null-terminated str2.
//If the strings are exactly equal, returns 0.
//On the first char found that differs, the function returns:
//-1 if the char from str2 is larger, 1 otherwise.
int strcmp(const char *str1, const char *str2)
{
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    size_t min = len1 < len2 ? len1 : len2;

    return memcmp(str1, str2, min);
}