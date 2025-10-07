#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stddef.h>

// CPU entry point
void cpu_run(unsigned char *memory, size_t mem_size);

#endif