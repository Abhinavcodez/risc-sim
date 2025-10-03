#include "cpu.h"

uint64_t regs[32];
uint64_t pc = 0;

void init_registers() {
    for(int i=0;i<32;i++) regs[i] = 0;
}