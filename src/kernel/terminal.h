#ifndef _TERMINAL_H
#define _TERMINAL_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "ps2_kb.h"

#define TERM_SCANNER_BUF_SZ 512

#ifndef __VGA_COLOR_ENUM
#define __VGA_COLOR_ENUM
typedef enum __vga_color {
    VGA_BLACK,
    VGA_BLUE,
    VGA_GREEN,
    VGA_CYAN,
    VGA_RED,
    VGA_MAGENTA,
    VGA_ORANGE,
    VGA_GREY,
    VGA_DGREY,
    VGA_BABYBLUE,
    VGA_LIME,
    VGA_TEAL,
    VGA_SCARLET,
    VGA_PINK,
    VGA_YELLOW,
    VGA_WHITE
} vga_color;
#endif

typedef union {
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

typedef struct {
    int16_t col;
    int16_t row;
} Term_Cursor;

struct Term_Scanner {
    bool scanning;
    uint16_t buf_ind;
    e_ps2_mods mods;
    e_ps2_locks locks;
    char buffer[TERM_SCANNER_BUF_SZ];
};

extern bool term_initialized;

void clear_term(void);
void tputc(char c);
void tcputc(vga_color bg, vga_color fg, char c);
void tputs(const char* s);
void tcputs(vga_color bg, vga_color fg, const char* s);
void twrite(const char* s, size_t len);
void tprintf(const char* format, ...);
void ttake_key(PS2_Key_Info key_info);
size_t tgets(size_t max, char* restrict buf);
char tgetc();
int8_t terminal_init(void);

#endif