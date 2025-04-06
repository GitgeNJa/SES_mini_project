#include <pthread.h>
#include "threading.h"

void *light_thread_func()
{
    logger(INFO, "Reading light sensor...\n");
    while (1)
    {
        read_light_reading();
    }
    pthread_exit(NULL);
}

void *fan_thread_func()
{
    logger(INFO, "Reading fan sensor...\n");
    while (1)
    {
        read_fan_reading();
    }
    pthread_exit(NULL);
}

void *ac_thread_func()
{
    logger(INFO, "Reading AC sensor...\n");
    while (1)
    {
        read_ac_reading();
    }
    pthread_exit(NULL);
}

int threading()
{
    pthread_t light_thread, fan_thread, ac_thread;
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

    return OK;
}
