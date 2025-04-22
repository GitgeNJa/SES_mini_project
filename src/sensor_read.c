#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>  // For rounding

#include "sensor_read.h"
#include "error_handler.h"

// Utility function to generate random float between min and max
double generate_random_value(double min, double max) {
    return ((double)rand() / RAND_MAX) * (max - min) + min;
}

// Utility function to round a value to two decimal places
double round_to_two_decimal(double value) {
    return round(value * 100.0) / 100.0;  // Round to 2 decimal places
}

int read_light_reading()
{
    double light_voltage_value = 230.0; // Standard Indian voltage
    double light_current_value = generate_random_value(0.02, 0.1); // 5W to 23W
    double light_power_value = light_voltage_value * light_current_value;
    light_power_value = round_to_two_decimal(light_power_value); // Limit to 2 decimal places

    if(!check_light_power(light_power_value))
    {
        logger(DEBUG, "Light sensor power value: %lf W\n", light_power_value);
        write_light_power_value(light_power_value);
    }
    sleep(3);
    return OK;
}

int read_fan_reading()
{
    double fan_voltage_value = 230.0;
    double fan_current_value = generate_random_value(0.1, 0.3); // ~23W to 69W
    double fan_power_value = fan_voltage_value * fan_current_value;
    fan_power_value = round_to_two_decimal(fan_power_value); // Limit to 2 decimal places

    if(!check_fan_power(fan_power_value))
    {
        logger(DEBUG, "Fan sensor power value: %lf W\n", fan_power_value);
        write_fan_power_value(fan_power_value);
    }
    sleep(5);
    return OK;
}

int read_ac_reading()
{
    double ac_voltage_value = 230.0;
    double ac_current_value = generate_random_value(4.0, 7.0); // ~920W to 1610W
    double ac_power_value = ac_voltage_value * ac_current_value;
    ac_power_value = round_to_two_decimal(ac_power_value); // Limit to 2 decimal places

    if(!check_ac_power(ac_power_value))
    {
        logger(DEBUG, "AC sensor power value: %lf W\n", ac_power_value);
        write_ac_power_value(ac_power_value);
    }
    sleep(10);
    return OK;
}

// Initialize RNG once at program start
void init_random_generator() {
    srand(time(NULL));
}
