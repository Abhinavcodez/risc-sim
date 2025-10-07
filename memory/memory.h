#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

// 32-bit read from memory
uint32_t mem_read32(unsigned char *memory, uint64_t addr);

// 64-bit read/write helpers
uint64_t load64(uint64_t addr, unsigned char *memory);
void store64(uint64_t addr, uint64_t val, unsigned char *memory);

#endif