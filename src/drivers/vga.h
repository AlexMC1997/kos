#ifndef _VGA_H
#define _VGA_H

#include <stdint.h>
#include "io.h"

extern const uint8_t VGA_COL_MAX;
extern const uint8_t VGA_ROW_MAX;
extern const uintptr_t VGA_START;
extern const uintptr_t VGA_END;

typedef uint8_t vga_attr;
typedef uint16_t vga_char;

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

typedef enum __crt_reg {
    REG_H_TOTAL,
    REG_H_END,
    REG_H_TOTAL_START,
    REG_H_TOTAL_END,
    REG_H_START_RETRACE,
    REG_H_END_RETRACE,
    REG_V_TOTAL,
    REG_OVF,
    REG_PRESET_ROW,
    REG_MAX_SCAN,
    REG_CURSOR_START,
    REG_CURSOR_END,
    REG_START_ADD_HIGH,
    REG_START_ADD_LOW,
    REG_CURSOR_LOC_HIGH,
    REG_CURSOR_LOC_LOW,
    REG_V_RETRACE_START,
    REG_V_RETRACE_END,
    REG_V_DISPLAY_END,
    REG_OFFSET,
    REG_UL_LOC,
    REG_V_BLANK_START,
    REG_V_BLANK_END,
    REG_CRTC_MODE,
    REG_LINE_CMP
} crt_reg;

typedef enum __attr_reg {
    REG_PAL_0,
    REG_PAL_1,
    REG_PAL_2,
    REG_PAL_3,
    REG_PAL_4,
    REG_PAL_5,
    REG_PAL_6,
    REG_PAL_7,
    REG_PAL_8,
    REG_PAL_9,
    REG_PAL_A,
    REG_PAL_B,
    REG_PAL_C,
    REG_PAL_D,
    REG_PAL_E,
    REG_PAL_F,
    REG_ATTR_MD_CONT,
} attr_reg;

struct vga_device {
    port16 MISC_OUT_REG_RD; 
    port16 MISC_OUT_REG_WR; 
    port16 CRT_ADD_REG; 
    port16 CRT_DATA_REG; 
    port16 ATTR_ADD_REG; 
    port16 ATTR_DATA_REG; 
    port16 IN_STAT_REG_1; 

    uint16_t* text_buffer;
};

uint8_t vga_init(void);
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