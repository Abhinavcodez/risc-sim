#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdarg.h>

// ANSI color codes
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_BOLD    "\033[1m"

// Logging macros with color labels
#define log_cpu(fmt, ...)    logger_log(COLOR_YELLOW "[CPU] " COLOR_RESET fmt, ##__VA_ARGS__)
#define log_mem(fmt, ...)    logger_log(COLOR_GREEN  "[MEM] " COLOR_RESET fmt, ##__VA_ARGS__)
#define log_tlb(fmt, ...)    logger_log(COLOR_CYAN   "[TLB] " COLOR_RESET fmt, ##__VA_ARGS__)
#define log_page(fmt, ...)   logger_log(COLOR_MAGENTA"[PAGE] " COLOR_RESET fmt, ##__VA_ARGS__)
#define log_error(fmt, ...)  logger_log(COLOR_RED    "[ERROR] " COLOR_RESET fmt, ##__VA_ARGS__)

void logger_log(const char *fmt, ...);

#endif