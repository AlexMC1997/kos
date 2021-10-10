#ifndef _PS2_H
#define _PS2_H

#include "io.h"
#include "stdint.h"

#define PS2_DATA 0x60
#define PS2_COM 0x64
#define PS2_STAT 0x64

typedef enum ps2_stat {
    PS2_OUT_BUF_EMPTY = 1,
    PS2_IN_BUF_FULL = 2,
    PS2_SYS_PASS = 4,
    PS2_DATA_COM = 8,
    PS2_UNKN1 = 16,
    PS2_UNKN2 = 32,
    PS2_TIMEOUT = 64,
    PS2_PARITY = 128,
} e_ps2_stat;

typedef enum ps2_com {
    PS2_COM_READN = 0x20,
    PS2_COM_WRITEN = 0x60,
    PS2_COM_DIS_PORT2 = 0xA7,
    PS2_COM_EN_PORT2 = 0xA8,
    PS2_COM_TEST_PORT2 = 0xA9,
    PS2_COM_TEST_CONT = 0xAA,
    PS2_COM_TEST_PORT1 = 0xAB,
    PS2_COM_DUMP = 0xAC,
    PS2_COM_DIS_PORT1 = 0xAD,
    PS2_COM_EN_PORT1 = 0xAE,
    PS2_COM_READ_CON_IN = 0xC0,
    PS2_COM_CPY_0_3 = 0xC1,
    PS2_COM_CPY_4_7 = 0xC2,
    PS2_COM_READ_CON_OUT = 0xD0,
    PS2_COM_WRITE_OUT = 0xD1,
    PS2_COM_WRITE_OUT_FIRST = 0xD2,
    PS2_COM_WRITE_OUT_SECOND = 0xD3,
    PS2_COM_WRITE_IN_SECOND = 0xD4
} e_ps2_com;

void ps2_init();
int ps2_get_byte(uint8_t* data);
int ps2_send_byte(uint8_t data);

#endif