#include "loader.h"
#include "logger.h"   // <-- important! must come before using log_error
#include <stdio.h>
#include <stdlib.h>

void load_binary(const char *filename, unsigned char *memory, size_t max_size) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        log_error("Failed to open file: %s", filename);
        return;
    }

    size_t bytes = fread(memory, 1, max_size, f);
    if (bytes == 0) {
        log_error("Failed to read binary file: %s", filename);
    } else {
        printf("[LOADER] Loaded %zu bytes from %s\n", bytes, filename);
    }

    fclose(f);
}