#include <pthread.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "threading.h"
#include "logger.h"
#include "sensor_read.h"
#include <sys/types.h>
#include <sys/stat.h>

#define CONTROL_PIPE "/tmp/smart_home_ctrl"

volatile int run_light = 1;
volatile int run_fan = 1;
volatile int run_ac = 1;

void *light_thread_func()
{
    logger(INFO, "Reading light sensor...\n");
    while (1)
    {
        if (run_light)
            read_light_reading();
        else
            sleep(1);
    }
    pthread_exit(NULL);
}

void *fan_thread_func()
{
    logger(INFO, "Reading fan sensor...\n");
    while (1)
    {
        if (run_fan)
            read_fan_reading();
        else
            sleep(1);
    }
    pthread_exit(NULL);
}

void *ac_thread_func()
{
    logger(INFO, "Reading AC sensor...\n");
    while (1)
    {
        if (run_ac)
            read_ac_reading();
        else
            sleep(1);
    }
    pthread_exit(NULL);
}

void *command_listener()
{
    char buffer[64];
    int fd;

    logger(INFO, "Starting command listener thread...\n");

    while (1)
    {
        fd = open(CONTROL_PIPE, O_RDONLY);
        if (fd < 0)
        {
            logger(ERROR, "Failed to open control pipe\n");
            sleep(1);
            continue;
        }
        
        memset(buffer, 0, sizeof(buffer));
        read(fd, buffer, sizeof(buffer));
        close(fd);
        buffer[strcspn(buffer, "\n")] = 0;
        if (strcmp(buffer, "light_on") == 0)
        {
            if (run_light == 0)
            {
                run_light = 1;
                logger(INFO, "Light turned ON\n");
            }
        }
        else if (strcmp(buffer, "light_off") == 0)
        {
            if (run_light == 1)
            {
                run_light = 0;
                logger(INFO, "Light turned OFF\n");
            }
        }
        else if (strcmp(buffer, "fan_on") == 0)
        {
            if (run_fan == 0)
            {
                run_fan = 1;
                logger(INFO, "Fan turned ON\n");
            }
        }
        else if (strcmp(buffer, "fan_off") == 0)
        {
            if (run_fan == 1)
            {
                run_fan = 0;
                logger(INFO, "Fan turned OFF\n");
            }
        }
        else if (strcmp(buffer, "ac_on") == 0)
        {
            if (run_ac == 0)
            {
                run_ac = 1;
                logger(INFO, "AC turned ON\n");
            }
        }
        else if (strcmp(buffer, "ac_off") == 0)
        {
            if (run_ac == 1)
            {
                run_ac = 0;
                logger(INFO, "AC turned OFF\n");
            }
        }
        else
        {
            logger(ERROR, "Unknown command: %s\n", buffer);
        }
    }

    pthread_exit(NULL);
}


void create_control_pipe()
{
    if (access(CONTROL_PIPE, F_OK) == -1)
    {
        if (mkfifo(CONTROL_PIPE, 0666) != 0)
        {
            logger(ERROR, "Failed to create control pipe\n");
            exit(EXIT_FAILURE);
        }
    }
}

int threading()
{
    pthread_t light_thread, fan_thread, ac_thread, cmd_thread;

    create_control_pipe();

    if (pthread_create(&light_thread, NULL, light_thread_func, NULL) != 0)
    {
        logger(ERROR, "Failed to create light thread\n");
        return NOT_OK;
    }

    if (pthread_create(&fan_thread, NULL, fan_thread_func, NULL) != 0)
    {
        logger(ERROR, "Failed to create fan thread\n");
        return NOT_OK;
    }

    if (pthread_create(&ac_thread, NULL, ac_thread_func, NULL) != 0)
    {
        logger(ERROR, "Failed to create AC thread\n");
        return NOT_OK;
    }

    if (pthread_create(&cmd_thread, NULL, command_listener, NULL) != 0)
    {
        logger(ERROR, "Failed to create command listener thread\n");
        return NOT_OK;
    }

    return OK;
}
