#ifndef _TERMINAL_H
#define _TERMINAL_H
#include <stdint.h>

void clear_term(void);
void tputc(char c);
void tputs(const char* s);
void twrite(const char* s, size_t len);
int8_t terminal_init(void);

#endif