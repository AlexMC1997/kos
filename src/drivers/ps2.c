#include "ps2.h"
#include "panic.h"

uint8_t ps2_read_data()
{
    register uint8_t reg_al asm("%al");
    inb(reg_al, PS2_DATA);
    return reg_al;
}

void ps2_write_data(uint8_t data)
{
    register uint8_t reg_al asm("%al") = data;
    outb(reg_al, PS2_DATA);
}

uint8_t ps2_read_stat()
{
    register uint8_t reg_al asm("%al");
    inb(reg_al, PS2_STAT);
    return reg_al;
}

void ps2_write_com(e_ps2_com data)
{
    register uint8_t reg_al asm("%al") = data;
    outb(reg_al, PS2_COM);
}

int ps2_get_byte(uint8_t* data)
{
    uint32_t sentry = 0;
    while (!(ps2_read_stat() & PS2_OUT_BUF_EMPTY)) {
        if (++sentry == 0xFFFF)
            return 0;
    }
    *data = ps2_read_data();
    return 1;
}

int ps2_send_byte(uint8_t data)
{
    uint32_t sentry = 0;
    while (ps2_read_stat() & PS2_IN_BUF_FULL) {
        if (++sentry == 0xFFFF)
            return 0;
    }
    ps2_write_data(data);
    return 1;
}

void ps2_init()
{
    uint8_t control = 0;
    ps2_write_com(PS2_COM_DIS_PORT1);
    ps2_write_com(PS2_COM_DIS_PORT2);
    ps2_read_data();

    ps2_write_com(PS2_COM_READN);
    if (!ps2_get_byte(&control))
        panic("PS2 controller initialization failed.");

    control &= 0b10111100;
    ps2_write_com(PS2_COM_WRITEN);
    ps2_send_byte(control);

    ps2_write_com(PS2_COM_TEST_CONT);
    if (!ps2_get_byte(&control))
        panic("PS2 controller initialization failed.");
    if (control != 0x55)
        panic("PS2 controller initialization failed.");
    
    // ps2_write_com(PS2_COM_EN_PORT2);
    // ps2_write_com(PS2_COM_READN);
    // if (!(ps2_get_byte() & 0b00100000))
    //     panic("PS2 controller initialization failed.");
    // ps2_write_com(PS2_COM_DIS_PORT2);
    
    ps2_write_com(PS2_COM_TEST_PORT1);
    if (!ps2_get_byte(&control))
        panic("PS2 controller initialization failed.");
    if (control)
        panic("PS2 controller initialization failed.");

    ps2_write_com(PS2_COM_TEST_PORT2);
    if (!ps2_get_byte(&control))
        panic("PS2 controller initialization failed.");
    if (control)
        panic("PS2 controller initialization failed.");

    ps2_write_com(PS2_COM_EN_PORT1);
    ps2_write_com(PS2_COM_EN_PORT2);

    ps2_write_com(PS2_COM_READN);
    if (!ps2_get_byte(&control))
        panic("PS2 controller initialization failed.");
    control |= 1;
    ps2_write_com(PS2_COM_WRITEN);
    if (!ps2_send_byte(control))
        panic("PS2 controller initialization failed.");
}