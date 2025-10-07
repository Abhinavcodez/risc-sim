#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>

void paging_init();
uint64_t translate_address(uint64_t vaddr);

#endif