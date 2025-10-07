#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdint.h>

void execute_instruction(uint32_t inst, uint64_t *regs, uint64_t *pc);

#endif