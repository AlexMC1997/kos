//high level vga text-mode interface

#include "vga.h"
#include "vgatext.h"

//generates vga character attribute
vga_attr vga_char_attr(vga_color bg, vga_color fg)
{
    return (vga_attr)(bg << 4 | fg);
}

//prints character to vga screen
void vga_putc(vga_attr attr, char c, uint16_t pos)
{
    vga.buffer[pos*2] = c;
    vga.buffer[(pos*2)+1] = attr;
}

//gets a vga char from screen buffer
vga_char vga_getc(uint16_t pos)
{
    return (vga.buffer[pos*2] | (vga.buffer[(pos*2)+1] << 8));
}

void vga_mv_cursor(uint16_t pos)
{
    vga_crtc_write(REG_CURSOR_LOC_LOW, (uint8_t)pos);
    vga_crtc_write(REG_CURSOR_LOC_HIGH, (uint8_t)(pos >> 8));
}

void vga_disable_cursor(void)
{
    vga_crtc_write(REG_CURSOR_START, 0x20);
}

//Enable/disable underline flag on text attribute
void vga_disable_underline(void)
{
    uint8_t tmp; 
    vga_crtc_read(REG_UL_LOC, &tmp);
    vga_crtc_write(REG_UL_LOC, tmp | 0x1F);
}

//Enable/disable blink flag on text attribute
void vga_disable_blink(void)
{
    uint8_t tmp;
    vga_attr_read(REG_ATTR_MD_CONT, &tmp);
    vga_attr_write(REG_ATTR_MD_CONT, (tmp & 0xF7));
}

void vga_text_init(void)
{
    uint8_t tmp;

    vga_device_init(&vga, (uint8_t*)VGA_START);

    //sets CRT registeraddress to 0x3D4/0x3D5 and stat reg to 0x3DA
    vga_misc_out_read(&tmp);
    vga_misc_out_write(tmp | (0x1 << FL_IOAS));

    //disables hardware cursor
    vga_disable_cursor();

    vga_disable_underline();

    vga_disable_blink();
}