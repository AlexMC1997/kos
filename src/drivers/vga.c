#pragma GCC push_options
#pragma GCC optimize("O0")

#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "io.h"
#include "vga.h"

//struct representing the VGA card
//do not change port numbers
struct vga_device vga;

const uint8_t VGA_COL_MAX = 80;
const uint8_t VGA_ROW_MAX = 25;
const uintptr_t VGA_START = 0xB8000;
const uintptr_t VGA_END = 0xBFFFF;

//Initilizes VGA struct. Screen buffer specified at buffer_start 
void vga_device_init(struct vga_device* v, uint8_t* buffer_start)
{
    v->MISC_OUT_REG_RD = (port16)0x3CC;
    v->MISC_OUT_REG_WR = (port16)0x32C;
    v->CRT_ADD_REG = (port16)0x3D4;
    v->CRT_DATA_REG = (port16)0x3D5;
    v->ATTR_ADD_REG = (port16)0x3C0;
    v->ATTR_DATA_REG = (port16)0x3C1;
    v->IN_STAT_REG_1 = (port16)0x3DA;

    v->buffer = buffer_start;
}

//Writes val to VGA Miscellaneous Output Registers
void vga_misc_out_write(uint8_t val)
{
    register uint8_t reg_al asm("%al") = val;
    outb(reg_al, vga.MISC_OUT_REG_WR);
}

//Reads VGA Miscellaneous Output Register to dest
void vga_misc_out_read(uint8_t* dest)
{
    register uint8_t reg_al asm("%al");
    inb(reg_al, vga.MISC_OUT_REG_RD);
    *dest = reg_al;
}

//Writes val to VGA CRT Control Register specified by reg.
void vga_crtc_write(crt_reg reg, uint8_t val)
{
    register uint8_t reg_al asm("%al") = reg;
    outb(reg_al, vga.CRT_ADD_REG);
    reg_al = val;
    outb(val, vga.CRT_DATA_REG);
}

//Reads from VGA CRT Control Register specified by reg.
//Places result in dest.
void vga_crtc_read(crt_reg reg, uint8_t* dest)
{
    register uint8_t reg_al asm("%al") = reg;
    outb(reg_al, vga.CRT_ADD_REG);
    inb(reg_al, vga.CRT_DATA_REG);
    *dest = reg_al;
}

//Writes val to VGA Attribute Data Register.
void vga_attr_write(attr_reg reg, uint8_t val) //Needs handling for palette writes
{
    register uint8_t reg_al asm("%al");
    inb(reg_al, vga.IN_STAT_REG_1); //sets addr reg to index
    reg_al = reg | 0x20; //Prevents PAS overwrite
    outb(reg_al, vga.ATTR_ADD_REG);
    reg_al = val;
    outb(reg_al, vga.ATTR_ADD_REG); //write data to addr register because vga
}

//Reads VGA Attribute Data Register to dest.
void vga_attr_read(attr_reg reg, uint8_t* dest)
{
    register uint8_t reg_al asm("%al");
    inb(reg_al, vga.IN_STAT_REG_1); //sets addr reg to index
    reg_al = reg | 0x20; //Prevents PAS overwrite
    outb(reg_al, vga.ATTR_ADD_REG);
    inb(reg_al, vga.ATTR_DATA_REG);
    *dest = reg_al;
}

#pragma GCC pop_options