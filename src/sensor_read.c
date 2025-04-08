#include "sensor_read.h"

FILE *sensor_write_file;
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

    sensor_write_file = fopen("./helper/light_sensor_value.txt", "a");
    if (sensor_write_file == NULL)
    {
        return 1;
    }
    fprintf(sensor_write_file, "%f\n", light_value);
    fclose(sensor_write_file);
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

    sensor_write_file = fopen("./helper/fan_sensor_value.txt", "a");
    if (sensor_write_file == NULL)
    {
        return 1;
    }
    fprintf(sensor_write_file, "%f\n", fan_value);
    fclose(sensor_write_file);
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

    sensor_write_file = fopen("./helper/ac_sensor_value.txt", "a");
    if (sensor_write_file == NULL)
    {
        return 1;
    }
    fprintf(sensor_write_file, "%f\n", ac_value);
    fclose(sensor_write_file);
    return OK;
}
