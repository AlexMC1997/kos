.global _trap_as
_trap_as:
    addl $4, %esp
    pushal
    call trap
_detrap_as:
    testl %eax, %eax
    jne _err_detrap__as
    popal
    addl $0x2, %esp
    iret
_err_detrap__as:
    popal
    addl $0x6, %esp
    iret