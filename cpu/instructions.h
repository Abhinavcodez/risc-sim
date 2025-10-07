#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdint.h>

// Execute one RISC-V instruction
void execute_instruction(uint32_t inst, uint64_t *regs, uint64_t *pc, unsigned char *memory);

#endif