#include "cpu/cpu.h"
#include "utils/loader.h"
#include <stdio.h>
#include <string.h>

// ANSI color codes for terminal
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define RESET   "\033[0m"

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <binary>\n", argv[0]);
        return 1;
    }

    unsigned char memory[65536] = {0};
    load_binary(argv[1], memory, sizeof(memory));

    // Run CPU simulation (memory + registers)
    cpu_run(memory, sizeof(memory));

    // Print memory accesses with TLB/Page info
    printf("\n=== Memory Dump (TLB + Page Info) ===\n");
    for (size_t addr = 0; addr < 0x1058; addr += 4) {
        uint32_t data = *((uint32_t*)(memory + addr));

        // Dummy TLB logic for demonstration
        int page = addr / 0x1000;
        int tlb_hit = (addr % 0x8) ? 1 : 0; // even addresses HIT, odd MISS

        printf("VA: 0x%04lx  DATA: 0x%08x  TLB: %s%s%s  Page: %s%d%s\n",
               addr,
               data,
               tlb_hit ? GREEN : RED,
               tlb_hit ? "HIT" : "MISS",
               RESET,
               BLUE,
               page,
               RESET
        );
    }

    // Print CPU registers
    printf("\n=== CPU Registers ===\n");
    for (int i = 0; i < 32; i++)
        printf("x%d = %lu\n", i, ((uint64_t*)memory)[i]);

    return 0;
}