    .section .data
msg:    
    .word 0x11223344
array:  
    .word 0x1, 0x2, 0x3, 0x4
gpu_array:
    .word 0,0,0,0  # will store GPU-simulated results

    .section .text
    .globl _start
_start:
    # Load msg into x1
    la x1, msg          
    lw x2, 0(x1)        # x2 = msg

    # Store value in array[2]
    la x3, array         
    li x4, 0xDEADBEEF
    sw x4, 8(x3)        

    # CPU arithmetic
    add x8, x2, x4      # x8 = msg + 0xDEADBEEF
    sub x9, x4, x2      # x9 = 0xDEADBEEF - msg

    # GPU-like vector add simulation
    la x5, array
    la x6, gpu_array
    li x7, 4            # number of elements

gpu_loop:
    lw x10, 0(x5)       # load array[i]
    lw x11, 0(x6)       # load gpu_array[i]
    add x12, x10, x11   # perform vector add
    sw x12, 0(x6)       # store result in gpu_array
    addi x5, x5, 4      # next array element
    addi x6, x6, 4
    addi x7, x7, -1
    bnez x7, gpu_loop

    # Infinite loop to halt CPU
halt:
    j halt