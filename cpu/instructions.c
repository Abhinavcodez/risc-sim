#include "instructions.h"
#include "alu.h"
#include "../memory/memory.h"
#include "../memory/paging.h"
#include "../gpu/gpu.h"
#include <stdint.h>

extern unsigned char memory[65536];  // global memory

void execute_instruction(uint32_t inst, uint64_t *regs, uint64_t *pc, unsigned char *memory) {
    uint8_t opcode = inst & 0x7F;
    uint8_t rd     = (inst >> 7) & 0x1F;
    uint8_t funct3 = (inst >> 12) & 0x7;
    uint8_t rs1    = (inst >> 15) & 0x1F;
    uint8_t rs2    = (inst >> 20) & 0x1F;
    uint8_t funct7 = (inst >> 25) & 0x7F;
    int32_t imm    = (int32_t)inst >> 20;

    switch(opcode) {
        case 0x33:  // R-type
            switch(funct3) {
                case 0: regs[rd] = (funct7 == 0x20) ? alu_sub(regs[rs1], regs[rs2]) 
                                                   : alu_add(regs[rs1], regs[rs2]); 
                        break;
                case 7: regs[rd] = alu_and(regs[rs1], regs[rs2]); break;
                case 6: regs[rd] = alu_or(regs[rs1], regs[rs2]); break;
                case 4: regs[rd] = alu_xor(regs[rs1], regs[rs2]); break;
            }
            break;

        case 0x03:  // Load
            regs[rd] = load64(translate_address(regs[rs1] + imm), memory);
            break;

        case 0x23:  // Store
            store64(translate_address(regs[rs1] + imm), regs[rs2], memory);
            break;

        case 0x13:  // Immediate arithmetic
            regs[rd] = regs[rs1] + imm;
            break;

        case 0xFF:  // Custom GPU instruction
            gpu_vector_add((uint64_t*)&memory[0], 
                           (uint64_t*)&memory[16], 
                           (uint64_t*)&memory[32], 4);
            break;

        default:
            // Unknown opcode
            break;
    }

    *pc += 4;  // advance program counter
}