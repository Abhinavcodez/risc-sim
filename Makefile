# =========================================================
# RISC-V Simulator Makefile (CPU + GPU + Memory + Utils)
# =========================================================

# Compiler setup
CC      = gcc
NVCC    = nvcc
CFLAGS  = -O2 -Wall -Icpu -Imemory -Iutils -Igpu
LDFLAGS = -lcudart
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
clean:
	@echo "[CLEAN]"
	rm -f $(OBJS) $(TARGET)

rebuild: clean all