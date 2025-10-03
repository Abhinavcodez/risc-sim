#include "cpu/cpu.h"
#include <stdio.h>

int main(int argc, char **argv){
    if(argc < 2){
        printf("Usage: %s <binary_file1> [binary_file2 ...]\n", argv[0]);
        return 1;
    }

    for(int i = 1; i < argc; i++){
        printf("\n=== Running %s ===\n", argv[i]);
        cpu_run(argv[i]);
    }

    return 0;
}