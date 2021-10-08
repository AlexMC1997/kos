#ifndef _TERMINAL_H
#define _TERMINAL_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

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
    uint16_t col;
    uint16_t row;
} Term_Cursor;

void clear_term(void);
void tputc(char c);
void tcputc(vga_color bg, vga_color fg, char c);
void tputs(const char* s);
void tcputs(vga_color bg, vga_color fg, const char* s);
void twrite(const char* s, size_t len);
void tprintf(const char* format, ...);
int8_t terminal_init(void);

#endif