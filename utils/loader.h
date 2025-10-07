#ifndef LOADER_H
#define LOADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

void load_binary(const char *filename, unsigned char *memory, size_t max_size);

#endif