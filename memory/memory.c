#include "memory.h"

unsigned char memory[MEMORY_SIZE];

uint64_t load64(uint64_t addr, unsigned char *memory) {
    return *(uint64_t*)&memory[addr];
}

void store64(uint64_t addr, uint64_t value, unsigned char *memory) {
    *(uint64_t*)&memory[addr] = value;
}