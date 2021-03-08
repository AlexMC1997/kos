.global _trap_as
_trap_as:
    addl $4, %esp
    pushl %eax
    pushl %ebx
    pushl %ecx
    pushl %edx
    pushl %esi
    pushl %edi
    pushl %ebp
    call trap
_detrap_as:
    popl %ebp
    popl %edi
    popl %esi
    popl %edx
    popl %ecx
    popl %ebx
    popl %eax
    addl $0x6, %esp
    iret