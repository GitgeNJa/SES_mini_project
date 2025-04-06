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
int light_sensor_write(float light_sensor_power)
{
    file = fopen("./helper/light.txt", "w");
    if (file == NULL)
    {
        return 1;
    }
    fprintf(file, "%f", light_sensor_power);
    fclose(file);
    return 0;
}
// save fan power value to file
int fan_sensor_write(float fan_sensor_power)
{
    file = fopen("./helper/fan.txt", "w");
    if (file == NULL)
    {
        return 1;
    }
    fprintf(file, "%f", fan_sensor_power);
    fclose(file);
    return 0;
}
// save AC power value to file
int ac_sensor_write(float ac_sensor_power)
{
    file = fopen("./helper/ac.txt", "w");
    if (file == NULL)
    {
        return 1;
    }
    fprintf(file, "%f", ac_sensor_power);
    fclose(file);
    return 0;
}

int main()
{
    while (1)
    {
        srand((unsigned int)time(NULL));
        float light_sensor_power = generate_random(5, 20);      // LED bulb
        float fan_sensor_power = generate_random(50, 80);       // Ceiling fan
        float ac_sensor_power = generate_random(700, 1800);     // Inverter AC

        if (light_sensor_write(light_sensor_power))
        {
            return 1;
        }
        if (fan_sensor_write(fan_sensor_power))
        {
            return 1;
        }
        if (ac_sensor_write(ac_sensor_power))
        {
            return 1;
        }

        // power change happening every five seconds
        sleep (5);
    }
    return 0;
}

