BITS 64

section .data
    x dq 10        ; Define x as a 64-bit variable

section .text
global _start
_start:
    mov rax, [rel x]    ; Use RIP-relative addressing to reference x
    ret