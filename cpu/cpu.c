#include "cpu.h"
#include "instructions.h"
#include "../memory/memory.h"
#include "../memory/paging.h"
#include "../memory/tlb.h"
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

#define MAX_CYCLES 1000000

void cpu_run(unsigned char *memory, size_t mem_size) {
    uint64_t regs[32] = {0};
    uint64_t pc = 0x0;
    int cycles = 0;

    paging_init();   // Initialize paging
    tlb_init();      // Initialize TLB

    while (pc < mem_size && cycles < MAX_CYCLES) {
        uint32_t inst = mem_read32(memory, pc);  // read 32-bit instruction
        // Optional: log_cpu("Fetched instruction 0x%08x at PC = 0x%016llx", inst, (unsigned long long)pc);
        execute_instruction(inst, regs, &pc, memory);
        cycles++;
    }

    printf("CPU halted after %d cycles\n", cycles);
    for (int i = 0; i < 32; i++)
        printf("x%d = %" PRIu64 "\n", i, regs[i]);
}