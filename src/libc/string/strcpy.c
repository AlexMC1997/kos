#include "string.h"
#include "stdint.h"

//Copies string at src to dest.
void* strcpy(char* dest, char* src)
{
    return memcpy(dest, src, strlen(src));
}