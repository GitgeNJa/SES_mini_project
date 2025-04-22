#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

#define OK 0
#define NOT_OK 1

typedef enum
{
    ERROR,
    INFO,
    DEBUG
} LogLevel;

void logger(LogLevel level, const char *format, ...);
void get_time(char *time_buffer, size_t buffer_size);
int write_light_power_value(double light_power_value);
int write_fan_power_value(double fan_power_value);
int write_ac_power_value(double ac_power_value);

#endif

