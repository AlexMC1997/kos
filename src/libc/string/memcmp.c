#include "string.h"
#include "stdint.h"

//Sums n bytes of str1 to n bytes of str2 then compares them.
//str1 > str2 returns 1
//str1 == str2 returns 0
//str1 < str2 returns -1
int memcmp(const void *str1, const void *str2, size_t n)
{
    uintmax_t sum1 = 0;
    uintmax_t sum2 = 0;
    uint8_t* str1_t = (uint8_t*)str1;
    uint8_t* str2_t = (uint8_t*)str2;
    
    for (size_t i = 0; i < n; i++) {
        sum1 += str1_t[i];
        sum2 += str2_t[i];
    }

    if (sum1 > sum2) 
        return 1;
    else if (sum2 > sum1) 
        return -1;
    else 
        return 0;
}