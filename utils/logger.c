#include <stdio.h>
#include <stdarg.h>
#include "logger.h"

// General CPU log
void log_cpu(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    printf("[CPU] ");
    vprintf(fmt, args);
    printf("\n");
    va_end(args);
}

// TLB log
void log_tlb(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    printf("[TLB] ");
    vprintf(fmt, args);
    printf("\n");
    va_end(args);
}

// Memory log
void log_memory(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    printf("[MEM] ");
    vprintf(fmt, args);
    printf("\n");
    va_end(args);
}

// Error log
void log_error(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    printf("[ERROR] ");
    vprintf(fmt, args);
    printf("\n");
    va_end(args);
}
