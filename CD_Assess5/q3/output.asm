section .data
a resw 1
b resw 1
c resw 1
d resw 1
e resw 1
t1 resw 1
t2 resw 1
t3 resw 1

section .text
global _start
_start:
    mov ax, [c]
    imul ax, [d]
    mov [t1], ax
    mov ax, [b]
    add ax, [t1]
    mov [t2], ax
    mov ax, [t2]
    sub ax, [e]
    mov [t3], ax

    mov ax, 1 ; exit syscall number
    int 0x80
