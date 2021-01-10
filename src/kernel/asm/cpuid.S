.section .text
.global _check_cpuid
.global _get_cpuid

.type _check_cpuid, @function
_check_cpuid:
    pushfl
    pushfl
    xorl $0x200000, (%esp)
    popfl
    pushfl
    popl %eax
    xorl (%esp), %eax
    popfl
    xorl $0x200000, %eax
    ret
.size _check_cpuid, . - _check_cpuid

.type _get_cpuid, @function
_get_cpuid:
    push %edi
    movl 8(%esp), %edi
    xorl %eax, %eax
    cpuid
    movl %ebx, (%edi)
    movl %edx, 4(%edi)
    movl %ecx, 8(%edi)
    movl $0, 12(%edi)
    movl $1, %eax
    cpuid
    movl %eax, 13(%edi)
    movl %ebx, 17(%edi)
    movl %ecx, 21(%edi)
    movl %edx, 25(%edi)
    pop %edi
    ret
.size _get_cpuid, . - _get_cpuid
