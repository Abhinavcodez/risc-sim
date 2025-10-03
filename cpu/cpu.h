#ifndef CPU_H
#define CPU_H

#include <stdint.h>

extern uint64_t regs[32];   // RISC-V general purpose registers
extern uint64_t pc;         // Program counter

void cpu_run(const char *binary_file);
void init_registers();
void execute_instruction(uint32_t inst);

#endif