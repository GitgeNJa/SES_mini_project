#include <stdarg.h>
#include <time.h>
#include <stdio.h>
#include "logger.h"

#define LOG_FILE_NAME "./helper/smart_home.log"  // Log file path for program logs

static LogLevel currentLogLevel = DEBUG;

// Function to get current timestamp
void get_time(char *time_buffer, size_t buffer_size)
{
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(time_buffer, buffer_size, "%Y-%m-%d %H:%M:%S", t);
}

// Function to convert log level to string
const char* logLevelToString(LogLevel level)
{
    switch (level)
    {
        case ERROR: return "ERROR";
        case INFO:  return "INFO";
        case DEBUG: return "DEBUG";
        default:    return "UNKNOWN";
    }
}

// General logger function
void logger(LogLevel level, const char *format, ...)
{
    if (level > currentLogLevel)
    {
        return;
    }

    va_list args;
    va_start(args, format);
    char time_buffer[64];
    get_time(time_buffer, sizeof(time_buffer));

    FILE *log_file = fopen(LOG_FILE_NAME, "a");  // Open log file for appending
    if (log_file != NULL)
    {
        fprintf(log_file, "[%s] [%s] ", time_buffer, logLevelToString(level));
        vfprintf(log_file, format, args);
        fclose(log_file);
    }
    va_end(args);
}
