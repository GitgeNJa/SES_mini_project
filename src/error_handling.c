#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "error_handling.h"

volatile sig_atomic_t sigint_received = 0;

void handle_sigint(int sig)
{
    logger(ERROR, "SIGINT (%d) received\n", sig);
    sigint_received = 1;
}

void exit_function()
{
    FILE *fp = popen("pidof sensor_mock", "r");
    if (!fp)
    {
        logger(ERROR, "Failed to run pidof\n");
        return;
    }

    char pid_buf[64];
    while (fgets(pid_buf, sizeof(pid_buf), fp) != NULL)
    {
        pid_t pid = (pid_t)atoi(pid_buf);
        if (pid > 0)
        {
            logger(ERROR, "Killing sensor_mock...\n");
            kill(pid, SIGKILL);
        }
    }
    pclose(fp);
    return;
}

void error_handling()
{
    signal(SIGINT, handle_sigint);
    while (!sigint_received)
    {
        sleep(3);
    }
    exit_function();

    logger(ERROR, "Exiting...\n\n\n");
    exit(0);
}
