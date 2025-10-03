#ifndef UTILS_H
#define UTILS_H
#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void log_info(const char *fmt, ...);
void load_binary(const char *file, unsigned char *memory, size_t max_size);

#ifdef __cplusplus
}
#endif

#endif