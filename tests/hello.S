    .section .text
    .globl _start

_start:
    li a0, 42          # Load 42 into a0
    li a1, 100         # Load 100 into a1
    add a2, a0, a1     # a2 = a0 + a1
    ebreak             # Stop execution
