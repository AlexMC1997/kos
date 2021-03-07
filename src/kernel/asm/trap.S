.global _trap_as
_trap_as:
    leal 4(%esp), %eax
    pushl %eax
    call trap
    add $0x0e, %esp
    iret