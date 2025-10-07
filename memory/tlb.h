#ifndef TLB_H
#define TLB_H

#include <stdint.h>

int tlb_lookup(uint64_t vaddr, uint64_t *paddr);

#endif