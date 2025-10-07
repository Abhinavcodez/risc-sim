#include "cpu/cpu.h"
#include "utils/loader.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <binary>\n", argv[0]);
        return 1;
    }

    unsigned char memory[65536] = {0};
    load_binary(argv[1], memory, sizeof(memory));

    cpu_run(memory, sizeof(memory));

    for (int i = 0; i < 32; i++)
        printf("x%d = %lu\n", i, ((uint64_t*)memory)[i]);
    return 0;
}