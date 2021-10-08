.global _trap_as
_trap_as:
    addl $4, %esp
    pushal
    call trap
_detrap_as:
    popal
    addl $0x6, %esp
    iret