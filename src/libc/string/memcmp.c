#include "string.h"
#include "stdint.h"

//Compares n bytes from ptr1 to n bytes from ptr2.
//If each byte is exactly equal, returns 0.
//On the first byte found that differs, the function returns:
//-1 if the byte from ptr2 is larger, 1 otherwise.
int memcmp(const void *ptr1, const void *ptr2, size_t n)
{
    if (ptr1 == ptr2)
        return 0;
        
    uint8_t* ptr1_t = (uint8_t*)ptr1;
    uint8_t* ptr2_t = (uint8_t*)ptr2;

    for (size_t i = 0; i < n; i++) {
        if (ptr1_t[i] > ptr2_t[i])
            return 1;
        if (ptr1_t[i] < ptr2_t[i])
            return -1;
    }

    return 0;
}