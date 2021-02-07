ENTRY(_prelude)

OUTPUT(./bin/osproj.bin)

SECTIONS
{   
    . = 1M;
    .multiboot BLOCK(4K) :
    {
        *(.multiboot)
        *(.prelude)
    }

    . = 0xC0100000 + SIZEOF (.multiboot);
    .text BLOCK(4K) : AT(ADDR(.text) - 0xC0000000)
    {
        *(.text)
    }

    .rodata BLOCK(4K) : AT(ADDR(.rodata) - 0xC0000000)
    {
        *(.rodata)
    }

    .data BLOCK(4K) : AT(ADDR(.data) - 0xC0000000)
    {
        *(.data)
    }

    .bss BLOCK(4K) : AT(ADDR(.bss) - 0xC0000000)
    {
        *(COMMON)
        *(.bss)
    _KERN_TEXT_END = .;
    }
}