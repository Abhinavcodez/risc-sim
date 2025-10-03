#include "../memory/memory.h"
#include <stdio.h>

void load_binary(const char *filename){
    FILE *f = fopen(filename,"rb");
    if(!f){
        printf("Failed to open %s\n", filename);
        return;
    }
    fread(memory, 1, MEMORY_SIZE, f); // use the extern memory
    fclose(f);
}