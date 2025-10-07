#include "cpu.h"
#include "instructions.h"
#include "../memory/memory.h"
#include "../memory/paging.h"
#include "../memory/tlb.h"
#include "../utils/logger.h"
#include <stdio.h>
#include <stdint.h>

#define MAX_CYCLES 100000

void cpu_run(unsigned char *memory, size_t mem_size) {
    uint64_t regs[32] = {0};
    uint64_t pc = 0x0;
    uint32_t inst;
    int cycles = 0;

    log_cpu("Starting CPU simulation (memory size = %zu bytes)", mem_size);

    while (pc < mem_size && cycles < MAX_CYCLES) {
        inst = *(uint32_t *)&memory[pc];
        log_cpu("Fetched instruction 0x%08x at PC = 0x%08llx", inst, (unsigned long long)pc);

        execute_instruction(inst, regs, &pc);
        cycles++;
    }

    log_cpu("CPU halted after %d cycles", cycles);
}