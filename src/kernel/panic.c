#pragma GCC push_options
#pragma GCC optimize("O0")

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "vga.h"
#include "io.h"
#include "panic.h"

#define panic_newline() text_cursor = (text_cursor + VGA_COL_MAX) - ((text_cursor + VGA_COL_MAX) % 80)

uint8_t PANIC_VIDEO_MODE = VGA_TEXT;

static uint8_t* screen_buffer;
static uint16_t text_cursor;
static vga_attr panic_color;

static void panic_write_vga(char* str)
{
    while (*str) {
        screen_buffer[text_cursor] = *str++;
        text_cursor += 2;
    }
}

static void vga_text_panic(char* panicmsg)
{
    bool valid_msg = false;

    screen_buffer = (uint8_t*)VGA_START;
    panic_color = (VGA_BLUE << 4) | VGA_WHITE;

    for (uint16_t i = 0; i < 2*(VGA_COL_MAX * VGA_ROW_MAX); i+=2) {
        screen_buffer[i] = ' ';
        screen_buffer[i+1] = panic_color;
    }

    panic_write_vga("Panic! System has encountered an irrecoverable error.");
    panic_newline();

    if (panicmsg) {
        for (uint16_t i = 0; i < 25; i++) {
            if (!panicmsg[i]) {
                valid_msg = true;
                break;
            }
        }
    }

    if (valid_msg) {
        panic_write_vga("Panic message: ");
        panic_write_vga(panicmsg);
    } else {
        panic_write_vga("Panic message could not be recovered");
    }
    panic_newline();

    asm("hlt");
}

//Prints error diagnostics, including panicmsg, then halts system. 
//panicmsg must be 25 characters or less. Does not return.
void panic(char* panicmsg)
{
    cli();
    switch (PANIC_VIDEO_MODE) {
        case VGA_TEXT:
        vga_text_panic(panicmsg);
    }
}

#pragma GCC pop_options