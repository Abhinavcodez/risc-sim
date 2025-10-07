#ifndef TLB_H
#define TLB_H

#include <stdint.h>

#define TLB_SIZE 16  // choose 8 or 16, keep consistent across all files

typedef struct {
    uint64_t vpn;
    uint64_t ppn;
    int valid;
} tlb_entry_t;

// TLB API
void tlb_init();
void tlb_add(uint64_t vaddr, uint64_t paddr);
int tlb_lookup(uint64_t vaddr, uint64_t *paddr);

// Optional memory helpers (if used in instructions.c)
void log_memory(const char *fmt, ...);
uint64_t load64(uint64_t addr, unsigned char *memory);
void store64(uint64_t addr, uint64_t val, unsigned char *memory);

#endif