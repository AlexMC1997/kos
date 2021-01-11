len = 256;
with open("./src/kernel/asm/ivt.S", 'w+') as f:
    f.write('.section .text\n')
    f.write('.extern _trap_as\n')
    f.write('.global _IVT_START\n')
    f.write('_IVT_START:\n')
    for i in range(len):
        f.write(f'.global isr_{i}\n')
        f.write(f'.type isr_{i}, @function\n')
        f.write(f'isr_{i}:\n')
        f.write(f'\tpushw ${i}\n')
        f.write('\tcall _trap_as\n\n')
    f.write('.global _IVT_ENTRY_LEN\n')
    f.write('_IVT_ENTRY_LEN:\n')
    f.write('.long isr_1 - _IVT_START\n')