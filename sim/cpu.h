#ifndef CPU_H
#define CPU_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MEM_SIZE 0x10000
extern uint8_t memory[MEM_SIZE];

typedef struct {
    uint64_t pc;
    uint64_t regs[32];
} cpu_t;

void cpu_init(cpu_t *cpu);
void cpu_load_program(cpu_t *cpu, const char *filename);
void cpu_run(cpu_t *cpu, int max_cycles);

// GPU interface
void cpu_launch_gpu_task();

#ifdef __cplusplus
}
#endif

#endif