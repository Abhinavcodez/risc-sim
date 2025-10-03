#include "cpu.h"
#include "../utils/utils.h"
#include "memory.h"
#include <stdio.h>

unsigned char memory[65536];

void cpu_run(const char *binary_file){
    init_registers();
    load_binary(binary_file, memory, 65536);

    pc = 0;

    // --- Special initialization for vecadd.bin ---
    if(strstr(binary_file,"vecadd.bin") != NULL){
        uint64_t *A = (uint64_t*)&memory[0];
        uint64_t *B = (uint64_t*)&memory[16];
        for(int i=0;i<4;i++){
            A[i] = i+1;     // 1,2,3,4
            B[i] = i+10;    // 10,11,12,13
        }
    }

    while(pc < 65536){
        uint32_t inst = *(uint32_t*)&memory[pc];
        execute_instruction(inst);
        pc += 4;
        // Stop if instruction is 0
        if(inst==0) break;
    }

    // --- Print results ---
    if(strstr(binary_file,"hello.bin") != NULL){
        printf("\n--- CPU Registers after hello.bin ---\n");
        for(int i=0;i<32;i++){
            printf("x%d = %lu\n",i,regs[i]);
        }
    }

    if(strstr(binary_file,"vecadd.bin") != NULL){
        uint64_t *C = (uint64_t*)&memory[32];
        printf("\n--- GPU Vector Add Results ---\n");
        for(int i=0;i<4;i++) printf("C[%d] = %lu\n",i,C[i]);
    }
}