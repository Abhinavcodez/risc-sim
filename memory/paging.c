#include "memory.h"
#include <stdio.h>
#include <stdint.h>

#define PAGE_SIZE 4096
#define NUM_PAGES 16

uint64_t page_table[NUM_PAGES];

void init_paging() {
    for(int i=0;i<NUM_PAGES;i++) page_table[i] = i*PAGE_SIZE;
}

// uint64_t translate_address(uint64_t virtual_addr){
//     uint64_t page = virtual_addr / PAGE_SIZE;
//     uint64_t offset = virtual_addr % PAGE_SIZE;
//     if(page >= NUM_PAGES){ printf("Page fault 0x%lx\n", virtual_addr); return 0; }
//     return page_table[page] + offset;
// }