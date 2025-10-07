#include "paging.h"
#include "memory.h"
#include "../utils/logger.h"
#include <stdint.h>

uint64_t translate_address(uint64_t vaddr) {
    // Example: identity mapping
    uint64_t paddr = vaddr; 
    log_tlb("VA 0x%llx -> PA 0x%llx", (unsigned long long)vaddr, (unsigned long long)paddr);
    return paddr;
}