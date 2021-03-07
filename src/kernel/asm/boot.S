//Multiboot constants
.set ALIGN, 1<<0 //align modules on page boundaries
.set MEMINFO, 1<<1 //provide memory map
.set FLAGS, ALIGN | MEMINFO //multiboot flag field
.set MAGIC, 0x1BADB002 //multiboot magic number
.set CHECKSUM, -(MAGIC + FLAGS) // multiboot checksum

//Multiboot Header
.section .multiboot, "a"
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

//Enables paging, remaps the kernel and then jumps to kernel entry
.section .prelude, "a", @progbits
.global _prelude
.type _prelude, @function
_prelude:
    cli

    xorl %ecx, %ecx
    xorl %edx, %edx
    movl $0b10000011, %edi
    
_build_dir_entry: //Builds the Kernel's identity page directory, 4 MiB pages
    movl %edi, (%ecx)
    addl $2, %ecx
    movb %dl, (%ecx)
    shlb $6, (%ecx)
    incl %ecx
    rorl $2, %edx
    movb %dl, (%ecx)
    roll $2, %edx
    incl %ecx
    incl %edx
    cmpl $0x200, %edx
    jnz _build_dir_entry

    //Adjust 3 GiB mapping to 0 - 4 MiB
    movl $0xC00, %ecx //3 GB
    movl $0x83, (%ecx)

    //Load the page directory
    xorl %edx, %edx
    movl %edx, %cr3

    //Enable large pages
    movl %cr4, %edx
    orl $0x10, %edx
    movl %edx, %cr4

    //Enable paging
    movl %cr0, %edx
    orl $0x80000000, %edx
    movl %edx, %cr0

    //Jump to the high kernel
    jmp _entry


//stack over bss
.section .bss
.align 16
stack_bottom:
.skip 0x4000 //16 kb stack
stack_top:

//Kernel Entry - no interrupts, protected mode
.section .text
.extern GDT_DESCRIPT_PTR
.global _entry
.type _entry, @function
_entry:
    //Initialize stack
    movl $stack_top, %esp

    //Push GRUB multiboot info onto stack for C entry
    push %ebx
    push %eax
    
    //FP init

    //Load GDT
    movl GDT_DESCRIPT_PTR, %eax
    lgdt (%eax)

    //Load segments
    ljmpl $0x8, $load_cs

load_cs:
    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss

    //Global constructors

    //C Entry
    call kern_main

    cli
    hlt
.loop:
    jmp .loop

.size _entry, . - _entry
    