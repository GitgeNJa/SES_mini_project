#include <stdarg.h>
#include <time.h>
#include "logger.h"

#define LOG_FILE_NAME "./helper/smart_home.log"
static LogLevel currentLogLevel = DEBUG;

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

void logger(LogLevel level, const char *format, ...)
{
    if (level > currentLogLevel)
    {
        return;
    }

    va_list args;
    va_start(args, format);
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char time_buffer[64];
    strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", t);

    FILE *log_file = fopen(LOG_FILE_NAME, "a");
    if (log_file != NULL)
    {
        fprintf(log_file, "[%s] [%s] ", time_buffer, logLevelToString(level));
        vfprintf(log_file, format, args);
        fclose(log_file);
    }
    va_end(args);
    return;
}
