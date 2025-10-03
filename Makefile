# Makefile for RISC-V CPU + GPU verification project
.PHONY: all clean

ELF = tests/hello.elf
BIN = tests/hello.bin
CPU_SIM = sim/sim_main

RISCV_GCC = riscv64-unknown-elf-gcc
RISCV_OBJCOPY = riscv64-unknown-elf-objcopy

CFLAGS = -O2 -std=c++17
CUDA_FLAGS = -O2

all: $(ELF) $(CPU_SIM)

# RISC-V ELF
# Build freestanding RISC-V ELF binary
$(ELF): tests/hello.c tests/link.ld
	riscv64-unknown-elf-gcc -march=rv64imac -mabi=lp64 -ffreestanding -nostdlib -T tests/link.ld -o $(ELF) tests/hello.c
	riscv64-unknown-elf-objcopy -O binary $(ELF) $(BIN)

# CPU simulation + GPU interface
# CPU simulation + GPU interface
$(CPU_SIM): sim/sim_main.cpp sim/cpu.c sim/cpu.h sim/gpu_interface.cu
	nvcc -std=c++17 -O2 sim/sim_main.cpp sim/cpu.c sim/gpu_interface.cu -o $(CPU_SIM)


clean:
	rm -f $(ELF) $(BIN) $(CPU_SIM)