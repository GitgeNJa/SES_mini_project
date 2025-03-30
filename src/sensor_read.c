#include <stdlib.h>
#include <unistd.h>
#include "sensor_read.h"

const char *light_filename = "./helper/light.txt";
const char *fan_filename = "./helper/fan.txt";
const char *ac_filename = "./helper/ac.txt";

int read_light_reading()
{
    FILE *file = fopen(light_filename, "r");
    if(file == NULL)
    {
        logger(ERROR, "Error opening light sensor file\n");
        return NOT_OK;
    }

    double light_value = 0;
    fscanf(file, "%lf", &light_value);
    logger(INFO, "Light sensor value: %lf\n", light_value);
    sleep (3);
    fclose(file);
    return OK;
}

int read_fan_reading()
{
    FILE *file = fopen(fan_filename, "r");
    if(file == NULL)
    {
        logger(ERROR, "Error opening fan sensor file\n");
        return NOT_OK;
    }

    double fan_value = 0;
    fscanf(file, "%lf", &fan_value);
    logger(INFO, "Fan sensor value: %lf\n", fan_value);
    sleep (5);
    fclose(file);
    return OK;
}

int read_ac_reading()
{
    FILE *file = fopen(ac_filename, "r");
    if(file == NULL)
    {
        logger(ERROR, "Error opening AC sensor file\n");
        return NOT_OK;
    }

    double ac_value = 0;
    fscanf(file, "%lf", &ac_value);
    logger(INFO, "AC sensor value: %lf\n", ac_value);
    sleep (10);
    fclose(file);
    return OK;
}
