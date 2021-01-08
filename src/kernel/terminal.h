#ifndef _TERMINAL_H
#define _TERMINAL_H
#include <stdint.h>

typedef union _tf_arg {
    char dhh;
    unsigned char uhh;
    short dh;
    unsigned short uh;
    unsigned int d;
    long l;
    unsigned long ul;
    long long dll;
    unsigned long long ull;
    size_t sz;
    const char* s;
    unsigned int x;
} tf_arg;

void clear_term(void);
void tputc(char c);
void tputs(const char* s);
void twrite(const char* s, size_t len);
void tprintf(const char* format, ...);
int8_t terminal_init(void);

#endif