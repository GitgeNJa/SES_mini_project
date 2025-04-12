#include <stdarg.h>
#include <time.h>
#include "logger.h"

#define LOG_FILE_NAME "./helper/smart_home.log"
#define DATABASE_NAME "./helper/power_sensor_value.txt"
FILE *sensor_write_file;
static LogLevel currentLogLevel = DEBUG;

void get_time(char *time_buffer, size_t buffer_size)
{
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(time_buffer, buffer_size, "%Y-%m-%d %H:%M:%S", t);
    return;
}

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
    char time_buffer[64];
    get_time(time_buffer, sizeof(time_buffer));

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

int write_light_power_value(double light_power_value)
{
    sensor_write_file = fopen(DATABASE_NAME, "a");
    if (sensor_write_file == NULL)
    {
        return NOT_OK;
    }
    char time_buffer[64];
    get_time(time_buffer, sizeof(time_buffer));
    fprintf(sensor_write_file, "%s [appliance_1] %f\n", time_buffer, light_power_value);
    fclose(sensor_write_file);
    return OK;
}

int write_fan_power_value(double fan_power_value)
{
    sensor_write_file = fopen(DATABASE_NAME, "a");
    if (sensor_write_file == NULL)
    {
        return NOT_OK;
    }
    char time_buffer[64];
    get_time(time_buffer, sizeof(time_buffer));
    fprintf(sensor_write_file, "%s [appliance_2] %f\n", time_buffer, fan_power_value);
    fclose(sensor_write_file);
    return OK;
}

int write_ac_power_value(double ac_power_value)
{
    sensor_write_file = fopen(DATABASE_NAME, "a");
    if (sensor_write_file == NULL)
    {
        return NOT_OK;
    }
    char time_buffer[64];
    get_time(time_buffer, sizeof(time_buffer));
    fprintf(sensor_write_file, "%s [appliance_3] %f\n", time_buffer, ac_power_value);
    fclose(sensor_write_file);
    return OK;
}
