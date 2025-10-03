#include "../memory/memory.h"
#include <string.h>
#include "../utils/utils.h"

// **define memory here only**
unsigned char memory[MEMORY_SIZE];

void init_memory(){
    memset(memory, 0, MEMORY_SIZE);
    log_info("Memory initialized\n");
}

uint64_t load64(uint64_t addr, unsigned char *mem){
    if(addr + 8 > MEMORY_SIZE) return 0;
    uint64_t val = 0;
    for(int i=0;i<8;i++) val |= ((uint64_t)mem[addr+i]) << (8*i);
    log_info("load64: addr=%llu val=%llu\n", addr, val);
    return val;
}

void store64(uint64_t addr, uint64_t value, unsigned char *mem){
    if(addr + 8 > MEMORY_SIZE) return;
    for(int i=0;i<8;i++) mem[addr+i] = (value >> (8*i)) & 0xFF;
    log_info("store64: addr=%llu val=%llu\n", addr, value);
}

uint64_t translate_address(uint64_t vaddr){
    log_info("translate_address: vaddr=%llu -> paddr=%llu\n", vaddr, vaddr);
    return vaddr;
}