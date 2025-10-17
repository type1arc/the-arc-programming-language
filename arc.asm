section .text
global _start

_start:
    mov eax, [x]
    add eax, [y]
    mov [sum], eax
    mov eax, 1
    int 0x80

section .data
x dd 10
y dd 20
sum dd 0
