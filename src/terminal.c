#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "vga.h"
#include "terminal.h"
#include "string.h"

uint16_t tcursor; 
uint16_t tmax;
vga_attr term_color;

int8_t tputc(char c)
{
    vga_putc(term_color, c, tcursor);
    tcursor = tcursor >= tmax ? 0 : tcursor + 1;
    vga_mv_cursor(tcursor);
    return 0;
}

int8_t twrite(char* s, size_t len)
{
    for (uint32_t ind = 0; ind < len; ind++)
        tputc(s[ind]);
    return 0;
}

int8_t tputs(char* s)
{
    return twrite(s, strlen(s));
}

int8_t terminal_init(void)
{
    tcursor = 0;
    tmax = (uint16_t)VGA_COL_MAX * VGA_ROW_MAX;
    term_color = vga_char_attr(VGA_BLACK, VGA_WHITE);

    //clear screen
    do tputc(0x20);
        while (tcursor);
    
    tputs("Terminal initialized.");

    return 0;
}