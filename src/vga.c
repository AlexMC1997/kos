#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "io.h"
#include "vga.h"


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

//struct representing the VGA card
//do not change port numbers
struct vga_device vga;

const uint8_t VGA_COL_MAX = 80;
const uint8_t VGA_ROW_MAX = 25;
const uintptr_t VGA_START = 0xB8000;

void vga_device_init(struct vga_device* v)
{
    v->MISC_OUT_REG_RD = (port16)0x3CC;
    v->MISC_OUT_REG_WR = (port16)0x32C;
    v->CRT_ADD_REG = (port16)0x3D4;
    v->CRT_DATA_REG = (port16)0x3D5;
    v->ATTR_ADD_REG = (port16)0x3C0;
    v->ATTR_DATA_REG = (port16)0x3C1;
    v->IN_STAT_REG_1 = (port16)0x3DA;

    v->text_buffer = (uint16_t*)VGA_START;
}

//generates vga character attribute
vga_attr vga_char_attr(vga_color bg, vga_color fg)
{
    return (vga_attr)(bg << 4 | fg);
}

//prints character to vga screen
void vga_putc(vga_attr attr, char c, uint16_t pos)
{
    vga.text_buffer[pos] = (uint16_t)attr << 8 | c;
}

void vga_mv_cursor(uint16_t pos)
{
    register uint8_t reg asm("%al") = REG_CURSOR_LOC_LOW; //because gcc sucks
    outb(reg, vga.CRT_ADD_REG);
    outb((uint8_t)pos, vga.CRT_DATA_REG);
    reg = REG_CURSOR_LOC_HIGH;
    outb(reg, vga.CRT_ADD_REG);
    outb((uint8_t)(pos >> 8), vga.CRT_DATA_REG);
}

void vga_disable_cursor(void)
{
    register uint8_t reg asm("%al") = REG_CURSOR_START;
    outb(reg, vga.CRT_ADD_REG);
    inb(reg, vga.CRT_DATA_REG);
    outb((uint8_t)(reg | 0x20), vga.CRT_DATA_REG);
}

void vga_enable_cursor(void)
{
    register uint8_t reg asm("%al") = REG_CURSOR_START;
    outb(reg, vga.CRT_ADD_REG);
    inb(reg, vga.CRT_DATA_REG);
    outb((uint8_t)(reg & 0xDF), vga.CRT_DATA_REG);
}


//Enable/disable underline flag on text attribute
void vga_disable_underline(void)
{
    register uint8_t reg asm("%al") = REG_UL_LOC;
    outb(reg, vga.CRT_ADD_REG);
    inb(reg, vga.CRT_DATA_REG);
    outb((uint8_t)(reg | 0x1F), vga.CRT_DATA_REG);
}

//Enable/disable blink flag on text attribute
void vga_disable_blink(void)
{
    register uint8_t reg asm("%al");
    inb(reg, vga.IN_STAT_REG_1); //sets addr reg to index
    reg = (uint8_t)(REG_ATTR_MD_CONT | 0x20);
    outb(reg, vga.ATTR_ADD_REG);
    inb(reg, vga.ATTR_DATA_REG);
    outb((uint8_t)(reg & 0xF7), vga.ATTR_ADD_REG);
}

//sets CRT register address to 0x3D4/0x3D5 and stat reg to 0x3DA
uint8_t vga_set_port(uint8_t a)
{
    uint8_t reg;
    
    if (a > 1)
        return -1;

    //set port address
    inb(reg, vga.MISC_OUT_REG_RD);
    outb((uint8_t)(reg | a), vga.MISC_OUT_REG_WR);

    return 0;
}

uint8_t vga_init(void)
{
    vga_device_init(&vga);

    vga_set_port((uint8_t)0x1);

    vga_disable_cursor();

    vga_disable_underline();

    vga_disable_blink();

    return 0;
}