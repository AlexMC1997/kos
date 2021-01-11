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
.extern GDT_DESCRIPT_PTR
.global _start
.type _start, @function
_start:
    cli

    //Initialize stack
    movl $stack_top, %esp

    //Push GRUB multiboot info onto stack for C
    push %ebx
    push %eax
    
    //FP init

    //Load GDT
    movl GDT_DESCRIPT_PTR, %eax
    lgdt (%eax)
    ljmpl $0x8, $load_cs

load_cs:
    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss

    //Enable paging

    //C++ init

    //C Entry
    call kern_main

    cli
    hlt
.loop:
    jmp .loop

.size _start, . - _start

//placeholder
.global _trap_as
_trap_as:
    movl $0x6028, %eax
    add $0x06, %esp
    iret
    