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

#endif

