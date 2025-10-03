#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void cpu_launch_gpu_task();

uint8_t memory[MEM_SIZE];

void cpu_init(cpu_t *cpu) {
    cpu->pc = 0x0;
    memset(cpu->regs, 0, sizeof(cpu->regs));
    memset(memory, 0, MEM_SIZE);
}

void cpu_load_program(cpu_t *cpu, const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) { perror("fopen"); exit(1); }
    fread(memory, 1, MEM_SIZE, f);
    fclose(f);
}

void cpu_run(cpu_t *cpu, int max_cycles) {
    for (int i = 0; i < max_cycles; i++) {
        uint8_t opcode = memory[cpu->pc];
        printf("PC: 0x%lx OPCODE: 0x%x\n", cpu->pc, opcode);

        // GPU trigger
        if (opcode == 0xFF) {
            printf("CPU triggering GPU kernel!\n");
            cpu_launch_gpu_task();
            break; // optional
        }

        cpu->pc++;
        if (cpu->pc >= MEM_SIZE) break;
    }
}