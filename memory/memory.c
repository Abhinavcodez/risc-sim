#include "memory.h"
#include "paging.h"
#include "tlb.h"
#include "../utils/logger.h"
#include <stdint.h>

uint32_t mem_read32(unsigned char *memory, uint64_t vaddr) {
    uint64_t paddr = translate_address(vaddr);  // get physical address via paging/TLB
    uint32_t val = *(uint32_t*)&memory[paddr];
    log_memory("READ32: VA 0x%016llx -> PA 0x%016llx = 0x%08x", 
               (unsigned long long)vaddr, (unsigned long long)paddr, val);
    return val;
}

void mem_write32(unsigned char *memory, uint64_t vaddr, uint32_t val) {
    uint64_t paddr = translate_address(vaddr);
    *(uint32_t*)&memory[paddr] = val;
    log_memory("WRITE32: VA 0x%016llx -> PA 0x%016llx = 0x%08x", 
               (unsigned long long)vaddr, (unsigned long long)paddr, val);
}

uint64_t load64(uint64_t addr, unsigned char *memory) {
    uint64_t val = *(uint64_t*)&memory[addr];
    log_memory("LOAD64: PA 0x%016llx = 0x%016llx", (unsigned long long)addr, val);
    return val;
}

void store64(uint64_t addr, uint64_t val, unsigned char *memory) {
    *(uint64_t*)&memory[addr] = val;
    log_memory("STORE64: PA 0x%016llx = 0x%016llx", (unsigned long long)addr, val);
}