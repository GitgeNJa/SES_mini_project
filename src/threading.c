
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "threading.h"

void *thread_func1()
{
    logger(INFO, "Reading light sensor...\n");
    sleep (1);
    while (1)
    {
        read_light_reading();
    }
    pthread_exit(NULL);
}

void *thread_func2()
{
    logger(INFO, "Reading fan sensor...\n");
    sleep (1);
    while (1)
    {
        read_fan_reading();
    }
    pthread_exit(NULL);
}

void *thread_func3()
{
    logger(INFO, "Reading AC sensor...\n");
    sleep (1);
    while (1)
    {
        read_ac_reading();
    }
    pthread_exit(NULL);
}

int threading()
{
    pthread_t thread1, thread2, thread3;
    int ret = NOT_OK;

    ret = pthread_create(&thread1, NULL, thread_func1, NULL);
    if (ret != 0)
    {
        logger(ERROR, "pthread_create failed for thread 1\n");
        return NOT_OK;
    }
    ret = pthread_create(&thread2, NULL, thread_func2, NULL);
    if (ret != 0)
    {
        logger(ERROR, "pthread_create failed for thread 2\n");
        return NOT_OK;
    }
    ret = pthread_create(&thread3, NULL, thread_func3, NULL);
    if (ret != 0)
    {
        logger(ERROR, "pthread_create failed for thread 3\n");
        return NOT_OK;
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    logger(INFO, "All threads have completed\n");
    return 0;
}
