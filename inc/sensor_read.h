#ifndef SENSOR_READ_H
#define SENSOR_READ_H

#include <stdlib.h>
#include <unistd.h>
#include "logger.h"

int read_light_reading();
int read_fan_reading();
int read_ac_reading();

#endif
