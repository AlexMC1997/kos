#include "pic.h"
#include "terminal.h"

pic master_pic;
pic slave_pic;

void pic_com(pic this, uint8_t command)
{   
    register uint8_t reg_al asm("%al") = command;
    outb(reg_al, this.com);
}

void pic_mask(pic this, uint8_t mask)
{   
    register uint8_t reg_al asm("%al") = mask;
    outb(reg_al, this.imr);
}

//Initialize Master PIC and Slave PIC
//IRQ 0-7 -> IVT 32-39
//IRQ 8-15 -> IVT 40-47 
void pic_init()
{
    master_pic.com = PIC_MASTER_COM;
    master_pic.com = PIC_MASTER_IMR;
    
    slave_pic.com = PIC_SLAVE_COM;
    slave_pic.com = PIC_SLAVE_IMR;

    pic_com(master_pic, PIC_ICW1);
    pic_com(slave_pic, PIC_ICW1);

    pic_com(master_pic, PIC_ICW2);
    pic_com(slave_pic, PIC_SLAVE_ICW2);

    pic_com(master_pic, PIC_ICW3);
    pic_com(slave_pic, PIC_SLAVE_ICW3);

    pic_com(master_pic, PIC_ICW4);
    pic_com(slave_pic, PIC_ICW4);

    pic_mask(master_pic, 0xFF);
    pic_mask(slave_pic, 0xFF);
}