#ifndef LOGGER_H
#define LOGGER_H

void log_cpu(const char *fmt, ...);
void log_tlb(const char *fmt, ...);
void log_memory(const char *fmt, ...);
void log_error(const char *fmt, ...); 

#endif