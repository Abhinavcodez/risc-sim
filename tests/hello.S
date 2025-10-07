    .section .data
msg:    
    .word 0x11223344
array:  
    .word 0x1, 0x2, 0x3, 0x4

    .section .text
    .globl _start
_start:
    # Load msg into x1
    la x1, msg          # x1 = VA of msg
    lw x2, 0(x1)        # x2 = memory[x1]

    # Store value in array[2]
    la x3, array         # x3 = VA of array
    li x4, 0xDEADBEEF
    sw x4, 8(x3)         # array[2] = 0xDEADBEEF

    # Use TLB multiple times
    lw x5, 0(x3)         # array[0]
    lw x6, 4(x3)         # array[1]
    lw x7, 8(x3)         # array[2] (should show TLB hit if reused)

    # Perform some arithmetic to check registers
    add x8, x2, x4
    sub x9, x4, x2

    # Custom GPU instruction to trigger GPU vector add
    li x10, 0xFF          # Custom opcode
    custom_gpu:
        addi x0, x0, 0    # NOP placeholder for simulation

    # Infinite loop to halt CPU
halt:
    j halt