#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "vga.h"
#include "terminal.h"
#include "string.h"

#define cursor_val (t_cursor[1] * VGA_COL_MAX) + t_cursor[0]

uint16_t t_cursor[2];
uint16_t vgamax;
vga_attr term_color;

//clears one row of the terminal; begins at 0
void clear_line(uint16_t row)
{
    uint16_t end = ((row + 1) * VGA_COL_MAX);
    for (uint16_t i = row * VGA_COL_MAX; i < end; i++) {
        vga_putc(term_color, ' ', i);
    }
}
//clears terminal screen
void clear_term(void)
{
    for (uint16_t i = 0; i < VGA_COL_MAX; i++) {
        clear_line(i);
    }
    t_cursor[0] = 0;
    t_cursor[1] = 0;
}

//scrolls terminal by 1 row
void term_scroll(void)
{
    const size_t end = (2*(VGA_COL_MAX * (VGA_ROW_MAX - 1)));
    uint8_t* p = (uint8_t*)(VGA_START + (VGA_COL_MAX * 2));
    memmove((uint8_t*)VGA_START, p, end);

    clear_line(VGA_ROW_MAX - 1);
}

//prints char to terminal
void tputc(char c)
{
    switch (c) {
        case '\n':
        t_cursor[0] = VGA_COL_MAX;
        break;

        case '\t':
        tputc(' ');
        tputc(' ');
        tputc(' ');
        tputc(' ');
        break;

        default:
        if (c < 0x20)
            break;
        vga_putc(term_color, c, cursor_val);
        t_cursor[0]++;
    }
    
    //handles new lines and scrolling
    if (t_cursor[0] >= VGA_COL_MAX) {
        t_cursor[0] = 0;
        t_cursor[1]++;
    }
    if (t_cursor[1] >= VGA_ROW_MAX) {
        t_cursor[1] = VGA_ROW_MAX - 1;
        term_scroll();
    }

    vga_mv_cursor(cursor_val);
}

//prints len chars to terminal
void twrite(char* s, size_t len)
{
    for (uint32_t ind = 0; ind < len; ind++)
        tputc(s[ind]);
}

//prints null-terminated string to terminal
void tputs(char* s)
{
    twrite(s, strlen(s));
}

//initializes terminal
int8_t terminal_init(void)
{
    term_color = vga_char_attr(VGA_BLACK, VGA_WHITE);

    clear_term();
    goto notest;
    
    //TESTING
    vga_color clr = VGA_WHITE;
    bool b = false;
    for (;;) {
        term_color = vga_char_attr(VGA_BLACK, clr);
        if (clr == 15)
            clr = 0;
        clr++;
        if (b) {
            tputc('\n');
            b = false;
        } else {
            tputs("Testing!");
            b = true;
        }
    }

    notest:
    tputs("Terminal initialized.");

    return 0;
}