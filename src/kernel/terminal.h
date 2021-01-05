#ifndef __terminal
#define __terminal
#include <stdint.h>

int8_t terminal_init(void);
int8_t tputc(char c);
int8_t tputs(char* s);
int8_t twrite(char* s, size_t len);

#endif