#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

FILE *file;

// function to generate random values within a range
float generate_random(float min, float max)
{
    return ((float)rand() / RAND_MAX) * (max - min) + min;      // RAND_MAX = 2147483647
}

// save light power value to file
int light_sensor_write(float light_sensor_voltage, float light_sensor_current)
{
    file = fopen("./helper/light.txt", "w");
    if (file == NULL)
    {
        return 1;
    }
    fprintf(file, "%f\n%f", light_sensor_voltage, light_sensor_current);
    fclose(file);
    return 0;
}
// save fan power value to file
int fan_sensor_write(float fan_sensor_voltage, float fan_sensor_current)
{
    file = fopen("./helper/fan.txt", "w");
    if (file == NULL)
    {
        return 1;
    }
    fprintf(file, "%f\n%f",fan_sensor_voltage, fan_sensor_current);
    fclose(file);
    return 0;
}
// save AC power value to file
int ac_sensor_write(float ac_sensor_voltage, float ac_sensor_current)
{
    file = fopen("./helper/ac.txt", "w");
    if (file == NULL)
    {
        return 1;
    }
    fprintf(file, "%f\n%f", ac_sensor_voltage, ac_sensor_current);
    fclose(file);
    return 0;
}

int main()
{
    while (1)
    {
        srand((unsigned int)time(NULL));
        float light_sensor_voltage = generate_random(207, 253);         // CFL bulb voltage
        float light_sensor_current = generate_random(0.065, 0.11);      // CFL bulb current
        float fan_sensor_voltage = generate_random(207, 253);           // Ceiling fan voltage
        float fan_sensor_current = generate_random(0.26, 0.35);         // Ceiling fan current
        float ac_sensor_voltage = generate_random(207, 253);            // Inverter AC voltage
        float ac_sensor_current = generate_random(3.7, 7.8);            // Inverter AC current

        if (light_sensor_write(light_sensor_voltage, light_sensor_current))
        {
            return 1;
        }
        if (fan_sensor_write(fan_sensor_voltage, fan_sensor_current))
        {
            return 1;
        }
        if (ac_sensor_write(ac_sensor_voltage, ac_sensor_current))
        {
            return 1;
        }

        // power change happening every five seconds
        sleep (5);
    }
    return 0;
}

