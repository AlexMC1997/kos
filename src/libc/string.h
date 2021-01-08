#ifndef _STRING_H
#define _STRING_H 

#include <stddef.h>
#include <stdint.h>

size_t strlen(const char *); 
void* memcpy(void* dest, void* src, size_t n);
void* memmove(void* dest, void* src, size_t n);
int memcmp(const void *str1, const void *str2, size_t n);
void* memchr(const void* str, char c, size_t n);
void* memset(void* str, uint8_t c, size_t n);
void* strcpy(char* dest, char* src);
void* strcat(char* dest, char* src);
void* strncpy(char* dest, char* src, size_t n);

#endif