#include "string.h"
#include "stdint.h"

//Appends string at src to the string at dest. 
void* strcat(char* dest, char* src)
{
    char* pivot = dest + strlen(dest);
    return strcpy(pivot, src);
}