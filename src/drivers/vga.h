#ifndef _VGA_H
#define _VGA_H

#include <stdint.h>
#include "io.h"

extern struct vga_device vga;

typedef enum __misc_out_flag {
    FL_IOAS,
    FL_RAM_EN,
    FL_CLK_SEL,
    FL_CLK_SEL_2,
    FL_OE_PG,
    FL_HSYNCP,
    FL_VSYNCP
} misc_out_flag;

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

    uint8_t* buffer;
};

void vga_misc_out_write(uint8_t val);
void vga_misc_out_read(uint8_t* dest);
void vga_crtc_write(crt_reg reg, uint8_t val);
void vga_crtc_read(crt_reg reg, uint8_t* dest);
void vga_device_init(struct vga_device* vga, uint8_t* buffer_start);

#endif