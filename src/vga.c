#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "io.h"
#include "vga.h"

const port16 CRT_ADD_REG = 0x3D4;
const port16 CRT_DATA_REG = 0x3D5;
const port16 MISC_OUT_REG_RD = 0x3CC;
const port16 MISC_OUT_REG_WR = 0x32C;
const port16 ATTR_ADD_REG = 0x3C0;
const port16 ATTR_DATA_REG = 0x3C1;
const port16 IN_STAT_REG_1 = 0x3DA;


const uint8_t VGA_COL_MAX = 80;
const uint8_t VGA_ROW_MAX = 25;
const uintptr_t VGA_START = 0xB8000;

uint16_t* vga_screen_buffer;

//generates vga character attribute
vga_attr vga_char_attr(vga_color bg, vga_color fg)
{
    return (vga_attr)(bg << 4 | fg);
}

//prints character to vga screen
void vga_putc(vga_attr attr, char c, uint16_t pos)
{
    vga_screen_buffer[pos] = (uint16_t)attr << 8 | c;
}

void vga_mv_cursor(uint16_t pos)
{
    register uint8_t reg asm("%al") = REG_CURSOR_LOC_LOW; //because gcc sucks
    outb(reg, CRT_ADD_REG);
    outb((uint8_t)pos, CRT_DATA_REG);
    reg = REG_CURSOR_LOC_HIGH;
    outb(reg, CRT_ADD_REG);
    outb((uint8_t)(pos >> 8), CRT_DATA_REG);
}

void vga_disable_cursor(void)
{
    register uint8_t reg asm("%al") = REG_CURSOR_START;
    outb(reg, CRT_ADD_REG);
    inb(reg, CRT_DATA_REG);
    outb((uint8_t)(reg | 0x20), CRT_DATA_REG);
}

void vga_enable_cursor(void)
{
    register uint8_t reg asm("%al") = REG_CURSOR_START;
    outb(reg, CRT_ADD_REG);
    inb(reg, CRT_DATA_REG);
    outb((uint8_t)(reg & 0xDF), CRT_DATA_REG);
}


//Enable/disable underline flag on text attribute
void vga_disable_underline(void)
{
    register uint8_t reg asm("%al") = REG_UL_LOC;
    outb(reg, CRT_ADD_REG);
    inb(reg, CRT_DATA_REG);
    outb((uint8_t)(reg | 0x1F), CRT_DATA_REG);
}

//Enable/disable blink flag on text attribute
void vga_disable_blink(void)
{
    register uint8_t reg asm("%al");
    inb(reg, IN_STAT_REG_1); //sets addr reg to index
    reg = (uint8_t)(REG_ATTR_MD_CONT | 0x20);
    outb(reg, ATTR_ADD_REG);
    inb(reg, ATTR_DATA_REG);
    outb((uint8_t)(reg & 0xF7), ATTR_ADD_REG);
}

//sets CRT register address to 0x3D4/0x3D5 and stat reg to 0x3DA
uint8_t vga_set_port(uint8_t a)
{
    uint8_t reg;
    
    if (a > 1)
        return -1;

    //set port address
    inb(reg, MISC_OUT_REG_RD);
    outb((uint8_t)(reg | a), MISC_OUT_REG_WR);

    return 0;
}

uint8_t vga_init(void)
{
    vga_screen_buffer = (uint16_t*)VGA_START;

    vga_set_port((uint8_t)0x1);

    vga_disable_cursor();

    vga_disable_underline();

    vga_disable_blink();

    return 0;
}