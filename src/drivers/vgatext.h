//high level vga text-mode interface
#ifndef _VGATEXT_H
#define _VGATEXT_H

#include <stdint.h>

typedef uint8_t vga_attr;
typedef uint16_t vga_char;

extern const int8_t VGA_COL_MAX;
extern const int8_t VGA_ROW_MAX;
extern const uintptr_t VGA_START;
extern const uintptr_t VGA_END;

#ifndef __VGA_COLOR_ENUM
#define __VGA_COLOR_ENUM
typedef enum {
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

void vga_text_init(void);
vga_attr vga_char_attr(vga_color bg, vga_color fg);
void vga_putc(vga_attr col, char c, uint16_t pos);
vga_char vga_getc(uint16_t pos);
void vga_mv_cursor(uint16_t pos);
void vga_disable_cursor(void);
void vga_enable_cursor(void);
void vga_disable_underline(void);
void vga_disable_blink(void);
void vga_text_scroll(void);

#endif