#include "memory.h"
#include <stdint.h>

#define TLB_SIZE 8
typedef struct { uint64_t virtual_page; uint64_t physical_page; int valid; } tlb_entry_t;
tlb_entry_t tlb[TLB_SIZE];

void init_tlb(){ for(int i=0;i<TLB_SIZE;i++) tlb[i].valid=0; }

uint64_t tlb_lookup(uint64_t virtual_addr){
    uint64_t page = virtual_addr / 4096;
    for(int i=0;i<TLB_SIZE;i++) if(tlb[i].valid && tlb[i].virtual_page==page)
        return tlb[i].physical_page*4096 + (virtual_addr%4096);
    tlb[0].valid=1; tlb[0].virtual_page=page; tlb[0].physical_page=page;
    return virtual_addr;
}