#include "cpu.h"
#include <iostream>

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: ./sim_main <elf-binary>\n";
        return 1;
    }

    cpu_t cpu;
    cpu_init(&cpu);
    cpu_load_program(&cpu, argv[1]);

    cpu_run(&cpu, 1000);
    return 0;
}