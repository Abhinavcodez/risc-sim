#include "tlb.h"
#include <stdint.h>
#include "../utils/logger.h"

int tlb_lookup(uint64_t vaddr, uint64_t *paddr) {
    int hit = 1; // for example, assume hit
    *paddr = vaddr; // identity mapping
    if(hit) {
        log_tlb("TLB HIT for VA 0x%lx -> PA 0x%lx\n", vaddr, *paddr);
    } else {
        log_tlb("TLB MISS for VA 0x%lx -> PA 0x%lx\n", vaddr, *paddr);
    }
    return hit;
}