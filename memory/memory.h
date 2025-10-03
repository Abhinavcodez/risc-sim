#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stdio.h>

#define MEMORY_SIZE 1024*64

// only declare extern
extern unsigned char memory[MEMORY_SIZE];

uint64_t load64(uint64_t addr, unsigned char *mem);
void store64(uint64_t addr, uint64_t value, unsigned char *mem);
uint64_t translate_address(uint64_t vaddr);
void init_memory();

#endif