#include "sensor_read.h"
#include "error_handler.h"

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

    double light_voltage_value = 0, light_current_value = 0, light_power_value = 0;
    fscanf(file, "%lf", &light_voltage_value);
    fscanf(file, "%lf", &light_current_value);
    light_power_value = light_voltage_value * light_current_value;
    fclose(file);

    if(!check_light_power(light_power_value))
    {
        logger(DEBUG, "Light sensor power value: %lf\n", light_power_value);
        sensor_write_file = fopen("./helper/light_sensor_value.txt", "a");
        if (sensor_write_file == NULL)
        {
            return 1;
        }
        fprintf(sensor_write_file, "%f\n", light_power_value);
        fclose(sensor_write_file);
    }
    sleep (3);
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

    double fan_voltage_value = 0, fan_current_value = 0, fan_power_value = 0;
    fscanf(file, "%lf", &fan_voltage_value);
    fscanf(file, "%lf", &fan_current_value);
    fan_power_value = fan_voltage_value * fan_current_value;
    fclose(file);

    if(!check_fan_power(fan_power_value))
    {
        logger(DEBUG, "Fan sensor power value: %lf\n", fan_power_value);
        sensor_write_file = fopen("./helper/fan_sensor_value.txt", "a");
        if (sensor_write_file == NULL)
        {
            return 1;
        }
        fprintf(sensor_write_file, "%f\n", fan_power_value);
        fclose(sensor_write_file);
    }
    sleep (5);
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

    double ac_voltage_value = 0, ac_current_value = 0, ac_power_value = 0;
    fscanf(file, "%lf", &ac_voltage_value);
    fscanf(file, "%lf", &ac_current_value);
    ac_power_value = ac_voltage_value * ac_current_value;
    fclose(file);

    if(!check_ac_power(ac_power_value))
    {
        logger(DEBUG, "AC sensor power value: %lf\n", ac_power_value);
        sensor_write_file = fopen("./helper/ac_sensor_value.txt", "a");
        if (sensor_write_file == NULL)
        {
            return 1;
        }
        fprintf(sensor_write_file, "%f\n", ac_power_value);
        fclose(sensor_write_file);
    }
    sleep (10);
    return OK;
}
