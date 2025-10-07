#include "tlb.h"
#include "../utils/logger.h"
#include <stdint.h>
#include <stdio.h>

static tlb_entry_t tlb[TLB_SIZE];

void tlb_init() {
    for (int i = 0; i < TLB_SIZE; i++) {
        tlb[i].valid = 0;
    }
}

int tlb_lookup(uint64_t vaddr, uint64_t *paddr) {
    uint64_t vpn = vaddr / 4096;
    uint64_t offset = vaddr % 4096;

    for (int i = 0; i < TLB_SIZE; i++) {
        if (tlb[i].valid && tlb[i].vpn == vpn) {
            *paddr = tlb[i].ppn * 4096 + offset;
            log_tlb("TLB HIT for VA 0x%016llx -> PA 0x%016llx", 
                    (unsigned long long)vaddr, (unsigned long long)*paddr);
            return 1; // Hit
        }
    }

    log_tlb("TLB MISS for VA 0x%016llx", (unsigned long long)vaddr);
    return 0; // Miss
}

void tlb_add(uint64_t vaddr, uint64_t paddr) {
    uint64_t vpn = vaddr / 4096;
    int idx = 0;

    // find first invalid slot
    for (int i = 0; i < TLB_SIZE; i++) {
        if (!tlb[i].valid) { idx = i; break; }
    }

    tlb[idx].vpn = vpn;
    tlb[idx].ppn = paddr / 4096;
    tlb[idx].valid = 1;

    log_tlb("TLB ADD VA 0x%016llx -> PA 0x%016llx", (unsigned long long)vaddr, (unsigned long long)paddr);
}