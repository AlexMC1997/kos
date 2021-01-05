//Multiboot constants
.set ALIGN, 1<<0 //align modules on page boundaries
.set MEMINFO, 1<<1 //provide memory map
.set FLAGS, ALIGN | MEMINFO //multiboot flag field
.set MAGIC, 0x1BADB002 //multiboot magic number
.set CHECKSUM, -(MAGIC + FLAGS) // multiboot checksum

//Multiboot Header
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

//stack over bss
.section .bss
.align 16
stack_bottom:
.skip 0x4000 //16 kb stack
stack_top:

//Kernel Entry - no paging, no interrupts, protected mode
.section .text
.global _start
.type _start, @function
_start:
    //Stack init
    movl $stack_top, %esp
    
    //FP init

    //Load GDT

    //Enable paging

    //C++ init

    //C Entry
    call kern_main

    cli
    hlt
.loop:
    jmp .loop

.size _start, . - _start

