#ifndef __terminal
#define __terminal
#include <stdint.h>

void clear_term(void);
void tputc(char c);
void tputs(const char* s);
void twrite(const char* s, size_t len);
int8_t terminal_init(void);

#endif