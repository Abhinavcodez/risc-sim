# 🧠 RISC-SIM: Paging, TLB, and CPU–GPU Memory Simulator

> A lightweight, educational RISC-V memory and execution simulator written in C — designed to visualize **virtual memory translation**, **TLB operations**, and **parallel CPU–GPU style computation**.

---

## 📘 Overview

**RISC-SIM** is a from-scratch simulation environment that demonstrates how a processor interacts with its **paging system**, **Translation Lookaside Buffer (TLB)**, and **memory subsystem** during binary execution.

The simulator loads a simple RISC-V binary (`hello.bin`) and performs:

* Instruction decoding and memory execution
* Virtual address translation and page tracking
* TLB hit/miss simulation
* Simulated GPU-style computation for parallel workloads

It’s built for **educational, experimental, and visualization** purposes — great for understanding **operating systems, architecture, and hardware memory management**.

---

## 🧩 Project Architecture

```
risc-sim/
├── cpu/
│   ├── alu.c
│   ├── alu.h
│   ├── cpu.c
│   ├── cpu.h
│   ├── instructions.c
│   ├── instructions.h
│   ├── registers.c
│   ├── registers.h
│   ├── alu.o
│   ├── cpu.o
│   ├── instructions.o
│   └── registers.o
│
├── gpu/
│   ├── gpu.cu
│   ├── gpu.h
│   ├── kernels.cu
│   ├── gpu.o
│   └── kernels.o
│
├── memory/
│   ├── memory.c
│   ├── memory.h
│   ├── paging.c
│   ├── paging.h
│   ├── tlb.c
│   ├── tlb.h
│   ├── memory.o
│   ├── paging.o
│   └── tlb.o
│
├── utils/
│   ├── loader.c
│   ├── loader.h
│   ├── logger.c
│   ├── logger.h
│   ├── loader.o
│   └── logger.o
│
├── tests/
│   ├── hello.S
│   ├── hello.o
│   ├── hello.elf
│   ├── hello.bin
│   ├── memtest.bin
│   └── vecadd.bin
│
├── main.c
├── main.o
├── Makefile
├── README.md
└── riscv_sim

```

---

## ⚙️ Installation

### 1. 🧹 Remove Old Spike (if installed)

If you previously installed Spike or similar RISC-V ISA simulators, remove them to avoid conflicts:

```bash
sudo rm -rf /usr/local/bin/spike /usr/local/bin/pk /usr/local/riscv
sudo rm -rf ~/riscv-isa-sim
```

### 2. 🛠️ Build the Simulator

```bash
cd ~/risc-sim-simulator
make clean
make
```

This will compile all components into the final binary:

```
./memsim
```

---

## 🚀 Running the Simulation

Execute your binary (`hello.bin`) through the simulator:

```bash
cd ~/risc-sim-simulator/src
./memsim ~/Desktop/risc-sim/tests/hello.bin
```

---

## 🧮 Example Output

```
=== Memory Dump (TLB + Page Info) ===

--- Page 1 ---
VA: 0x1000  DATA: 0x00000000  TLB: MISS
VA: 0x1004  DATA: 0x11223344  TLB: HIT
VA: 0x1008  DATA: 0x00000001  TLB: MISS
VA: 0x100C  DATA: 0x00000002  TLB: HIT
...

Total TLB Hits: 12, Misses: 12

=== CPU Registers ===
x0 = 0x0000000000000000
x1 = 0x0000000000000100
x8 = 0x00000000aabbccdd
x9 = 0x0000000012345678
```

---

## 🎨 Visualization Features

| Feature               | Description                                            |
| --------------------- | ------------------------------------------------------ |
| 🧠 **CPU Execution**  | Simulates register operations and data movement        |
| 🗂️ **Paging System** | Each 4 KB page is tracked with its base address        |
| 🧾 **TLB**            | Hit/Miss logic simulated per instruction access        |
| 🎮 **GPU Mode**       | Demonstrates parallel data computation zones in memory |
| 🌈 **Color Output**   | ANSI colors for pages, hits, misses, and registers     |

**Color Legend:**

* 🟩 Green → TLB Hit
* 🟥 Red → TLB Miss
* 🟦 Blue → CPU memory region
* 🟦 Cyan → GPU simulated memory
* 🟨 Yellow → Highlighted computation registers

---

## 🧠 Educational Value

RISC-SIM is ideal for:

* 🧩 Understanding **address translation** and **page mapping**
* 🔬 Studying **TLB efficiency** and **memory access patterns**
* 💡 Demonstrating **CPU–GPU heterogeneous computing** concepts
* 🧑‍🏫 Teaching **computer architecture** or **OS memory management**

---

## 🧰 Requirements

| Component                       | Version                |
| ------------------------------- | ---------------------- |
| GCC / G++                       | ≥ 9.0                  |
| Make                            | Any                    |
| RISC-V GNU Toolchain (optional) | For assembling hello.S |

---

## 🧑‍💻 Development Notes

To modify or add your own test program:

```bash
cd tests
riscv64-unknown-elf-as hello.S -o hello.o
riscv64-unknown-elf-objcopy -O binary hello.o hello.bin
```

Then run:

```bash
./memsim ./tests/hello.bin
```

---

## 🧩 Example Experiment Ideas

* Implement **multi-level page tables**.
* Extend TLB to simulate **LRU replacement**.
* Add a **cache simulator** layer.
* Simulate **DMA or shared memory between CPU & GPU**.
* Use actual **parallel threads** to mimic GPU execution.

---

## 🧠 Authors & Credits

**Project by:**

> Abhinavcodez
