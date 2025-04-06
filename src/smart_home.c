#include "smart_home.h"

void sensor_mock()
{
    pid_t pid = fork();
    if (pid < 0)
    {
        logger(ERROR, "Fork failed!\n");
    } 
    else if (pid == 0)
    {
        logger(INFO, "Mocking sensor readings...\n");
        if (execl("./helper/sensor_mock", "sensor_mock", (char *)NULL) == -1)
        {
            logger(ERROR, "execl failed!\n");
            exit(EXIT_FAILURE);
        }
    }
    return;
}

int main()
{
    logger(ERROR, "\n\n\n");
    logger(ERROR, "Welcome to Smart Home\n");
    sensor_mock();
    if (threading() == NOT_OK)
    {
        return NOT_OK;
    }
    error_handling();
    return OK;
}
