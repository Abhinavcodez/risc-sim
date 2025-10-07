# =========================================================
# RISC-V Simulator Makefile (CPU + GPU + Memory + Utils)
# =========================================================

# Compiler setup
CC      = gcc
NVCC    = nvcc
LDFLAGS = -no-pie -lcudart
CFLAGS  = -O2 -Wall -no-pie -Icpu -Imemory -Iutils -Igpu
TARGET  = riscv_sim

# Folder structure
CPU_SRCS     = $(wildcard cpu/*.c)
MEM_SRCS     = $(wildcard memory/*.c)
UTIL_SRCS    = $(wildcard utils/*.c)
GPU_SRCS     = $(wildcard gpu/*.cu)
MAIN_SRC     = main.c

# Object files
CPU_OBJS     = $(CPU_SRCS:.c=.o)
MEM_OBJS     = $(MEM_SRCS:.c=.o)
UTIL_OBJS    = $(UTIL_SRCS:.c=.o)
GPU_OBJS     = $(GPU_SRCS:.cu=.o)
MAIN_OBJ     = $(MAIN_SRC:.c=.o)

# Paths for RISC-V test
TEST_SRC = tests/hello.S
TEST_OBJ = tests/hello.o
TEST_ELF = tests/hello.elf
TEST_BIN = tests/hello.bin

# RISC-V toolchain
RISCV_AS      = riscv64-unknown-elf-as
RISCV_LD      = riscv64-unknown-elf-ld
RISCV_OBJCOPY = riscv64-unknown-elf-objcopy

OBJS = $(CPU_OBJS) $(MEM_OBJS) $(UTIL_OBJS) $(GPU_OBJS) $(MAIN_OBJ)

# =========================================================
# Default target
# =========================================================
all: $(TARGET)

# Link all components
$(TARGET): $(OBJS)
	@echo "[LD] Linking..."
	$(CC) -o $@ $(OBJS) $(LDFLAGS)
	@echo "✅ Build complete: $(TARGET)"

# =========================================================
# Test target: build and run hello test
# =========================================================
.PHONY: test-hello
test-hello: $(TEST_BIN) $(TARGET)
	@echo "=== Running hello test ==="
	./riscv_sim $(TEST_BIN)

# Step 1: Assemble hello.S
$(TEST_OBJ): $(TEST_SRC)
	@echo "[RISCV AS] Assembling $<"
	$(RISCV_AS) -o $@ $<

# Step 2: Link to ELF
$(TEST_ELF): $(TEST_OBJ)
	@echo "[RISCV LD] Linking $<"
	$(RISCV_LD) -o $@ $<

# Step 3: Convert ELF to raw binary
$(TEST_BIN): $(TEST_ELF)
	@echo "[OBJCOPY] Converting $< -> $@"
	$(RISCV_OBJCOPY) -O binary $< $@

# =========================================================
# Compilation rules
# =========================================================
cpu/%.o: cpu/%.c
	@echo "[CC] $<"
	$(CC) $(CFLAGS) -c $< -o $@

memory/%.o: memory/%.c
	@echo "[CC] $<"
	$(CC) $(CFLAGS) -c $< -o $@

utils/%.o: utils/%.c
	@echo "[CC] $<"
	$(CC) $(CFLAGS) -c $< -o $@

gpu/%.o: gpu/%.cu
	@echo "[NVCC] $<"
	$(NVCC) -c $< -o $@

%.o: %.c
	@echo "[CC] $<"
	$(CC) $(CFLAGS) -c $< -o $@

# =========================================================
# Housekeeping
# =========================================================
.PHONY: clean rebuild

clean:
	@echo "[CLEAN] Removing objects, binaries, and test files"
	rm -f $(OBJS) $(TARGET) $(TEST_OBJ) $(TEST_ELF) $(TEST_BIN)

rebuild: clean all