    .section .data
msg:    
    .word 0x11223344

array:  
    .word 0x1, 0x2, 0x3, 0x4

vec_a:
    .word 1,2,3,4,5,6,7,8
vec_b:
    .word 10,20,30,40,50,60,70,80
vec_c:
    .space 32        # to store vector result

sum_res: 
    .word 0

    .section .text
    .globl _start
_start:
    # --- Load scalar msg ---
    la x1, msg          # x1 = VA of msg
    lw x2, 0(x1)        # x2 = memory[x1]

    # --- Store a constant into array[2] ---
    la x3, array
    li x4, 0xDEADBEEF
    sw x4, 8(x3)        # array[2] = 0xDEADBEEF

    # --- Read array elements to trigger TLB hits/misses ---
    lw x5, 0(x3)
    lw x6, 4(x3)
    lw x7, 8(x3)

    # --- Simple arithmetic ---
    add x8, x2, x4      # x8 = msg + 0xDEADBEEF
    sub x9, x4, x2      # x9 = 0xDEADBEEF - msg

    # --- GPU-like vector addition ---
    la x10, vec_a        # base of vector A
    la x11, vec_b        # base of vector B
    la x12, vec_c        # base of vector C
    li x13, 8            # vector length

vec_loop:
    lw x14, 0(x10)       # load vec_a[i]
    lw x15, 0(x11)       # load vec_b[i]
    add x16, x14, x15    # vec_c[i] = a[i] + b[i]
    sw x16, 0(x12)       # store result

    addi x10, x10, 4     # i++
    addi x11, x11, 4
    addi x12, x12, 4
    addi x13, x13, -1
    bnez x13, vec_loop

    # --- Vector accumulation ---
    la x10, vec_c
    li x17, 8
    li x18, 0           # sum = 0

acc_loop:
    lw x19, 0(x10)
    add x18, x18, x19
    addi x10, x10, 4
    addi x17, x17, -1
    bnez x17, acc_loop

    # Store accumulated sum
    la x20, sum_res
    sw x18, 0(x20)

    # --- Infinite loop to halt CPU ---
halt:
    j halt