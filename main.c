#include "cpu/cpu.h"
#include "utils/loader.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

// ANSI color codes
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define RESET   "\033[0m"

#define MEM_SIZE 0x20000  // 128 KB memory

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <binary>\n", argv[0]);
        return 1;
    }

    unsigned char memory[MEM_SIZE] = {0};
    load_binary(argv[1], memory + 0x1000, MEM_SIZE - 0x1000);

    cpu_run(memory, MEM_SIZE);

    // Counters
    int tlb_hits = 0, tlb_misses = 0;

    printf("\n=== Memory Dump (TLB + Page Info) ===\n");
    int current_page = -1;
    for (size_t addr = 0x1000; addr < 0x1060; addr += 4) {
        uint32_t data = *((uint32_t*)(memory + addr));
        int page = addr / 0x1000;
        int tlb_hit = (addr / 4) % 2;  // dummy simulation

        if (page != current_page) {
            printf("\n%s--- Page %d --- %s\n", MAGENTA, page, RESET);
            current_page = page;
        }

        if (tlb_hit) tlb_hits++;
        else tlb_misses++;

        // Different colors for CPU vs GPU memory
        const char *color = BLUE; // default CPU
        if (addr >= 0x1010 && addr < 0x1020) color = CYAN; // gpu_array simulated

        printf("VA: 0x%04lx  DATA: 0x%08x  TLB: %s%s%s\n",
               addr,
               data,
               tlb_hit ? GREEN : RED,
               tlb_hit ? "HIT" : "MISS",
               RESET);
    }

    printf("\nTotal TLB Hits: %s%d%s, Misses: %s%d%s\n",
           GREEN, tlb_hits, RESET, RED, tlb_misses, RESET);

    // Registers stored at memory[0x0000..0x00ff]
    printf("\n=== CPU Registers ===\n");
    for (int i = 0; i < 32; i++) {
        uint64_t reg_val = *((uint64_t*)(memory + i * 8));
        const char *reg_color = (i >= 8 && i <= 12) ? YELLOW : RESET; // highlight computed regs
        printf("x%d = %s0x%016lx%s\n", i, reg_color, reg_val, RESET);
    }

    return 0;
}