#include "paging.h"
#include "tlb.h"
#include "../utils/logger.h"
#include <stdint.h>
#include <stdio.h>

void paging_init() {
    tlb_init();  // Initialize TLB
}

uint64_t translate_address(uint64_t vaddr) {
    uint64_t paddr;

    // Try TLB
    if (!tlb_lookup(vaddr, &paddr)) {
        // For now, identity mapping: VA -> PA
        paddr = vaddr;
        tlb_add(vaddr, paddr); // update TLB
    }

    log_tlb("VA 0x%016llx -> PA 0x%016llx", (unsigned long long)vaddr, (unsigned long long)paddr);
    return paddr;
}