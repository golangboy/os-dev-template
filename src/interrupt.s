[bits 32]
extern idt_handler;
global idt_table
section .data
idt_table:
%macro idt 2
section .text
idt_%1_entry:
cli
push %1 ;Vector
push %2 ;ERROR CODE
call idt_handler
add esp,4*2

sti
iretd
section .data
dd idt_%1_entry
%endmacro
idt 0,0
idt 1,0
idt 2,0
idt 3,0
idt 4,0
idt 5,0
idt 6,0
idt 7,0
idt 8,0
idt 9,0
idt 10,0
idt 11,0
idt 12,0
idt 13,0
idt 14,0
idt 15,0
idt 16,0
idt 17,0
idt 18,0
idt 19,0
idt 20,0
idt 21,0
idt 22,0
idt 23,0
idt 24,0
idt 25,0
idt 26,0
idt 27,0
idt 28,0
idt 29,0
idt 30,0
idt 31,0