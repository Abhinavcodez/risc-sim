#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stddef.h>

extern uint64_t regs[32];
extern uint64_t pc;

void cpu_run(unsigned char *memory, size_t mem_size);

#endif