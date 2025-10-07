#include "logger.h"
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

void logger_log(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    // Optional: timestamp
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char time_str[9];
    strftime(time_str, sizeof(time_str), "%H:%M:%S", tm_info);

    // Print timestamp + message
    printf(COLOR_BOLD "[%s] " COLOR_RESET, time_str);
    vprintf(fmt, args);
    printf("\n");

    va_end(args);
}