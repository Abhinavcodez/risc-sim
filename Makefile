# Makefile for riscv_sim

# Compilers
CC = gcc
NVCC = nvcc

# Flags
CFLAGS = -O2 -Wall
LDFLAGS = -lcudart

# Sources
CPU_SRC = cpu/*.c
MEM_SRC = memory/*.c
UTIL_SRC = utils/*.c
GPU_OBJ = gpu.o
MAIN = main.c

# Output
TARGET = riscv_sim

# Default target
all: $(TARGET)

# Compile GPU CUDA code
gpu.o: gpu/gpu.cu
	$(NVCC) -c gpu/gpu.cu -o gpu.o

# Compile and link everything
$(TARGET): $(MAIN) $(CPU_SRC) $(MEM_SRC) $(UTIL_SRC) $(GPU_OBJ)
	$(CC) $(CFLAGS) $(MAIN) $(CPU_SRC) $(MEM_SRC) $(UTIL_SRC) $(GPU_OBJ) $(LDFLAGS) -o $(TARGET)

# Clean build files
clean:
	rm -f $(TARGET) $(GPU_OBJ)

# Run all tests
run: $(TARGET)
	@echo "\n=== Running CPU Verification (hello.bin) ==="
	./$(TARGET) tests/hello.bin
	@echo "\n=== Running GPU Verification (vecadd.bin) ==="
	./$(TARGET) tests/vecadd.bin
	@echo "\n=== Running Memory / Paging / TLB Verification (memtest.bin) ==="
	./$(TARGET) tests/memtest.bin