#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

#define MEMORY_SIZE 65536
extern unsigned char memory[MEMORY_SIZE];

uint64_t load64(uint64_t addr, unsigned char *memory);
void store64(uint64_t addr, uint64_t value, unsigned char *memory);

#endif