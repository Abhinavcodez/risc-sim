#ifndef ALU_H
#define ALU_H

#include <stdint.h>

uint64_t alu_add(uint64_t a, uint64_t b);
uint64_t alu_sub(uint64_t a, uint64_t b);
uint64_t alu_and(uint64_t a, uint64_t b);
uint64_t alu_or(uint64_t a, uint64_t b);
uint64_t alu_xor(uint64_t a, uint64_t b);
uint64_t alu_sll(uint64_t a, uint64_t b);
uint64_t alu_srl(uint64_t a, uint64_t b);
uint64_t alu_sra(uint64_t a, uint64_t b);
uint64_t alu_slt(uint64_t a, uint64_t b);
uint64_t alu_sltu(uint64_t a, uint64_t b);

#endif