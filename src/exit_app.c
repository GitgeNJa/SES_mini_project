#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "exit_app.h"
#include "db.h"

volatile sig_atomic_t sigint_received = 0;
FILE *file;

void handle_sigint(int sig)
{
    logger(ERROR, "SIGINT (%d) received\n", sig);
    sigint_received = 1;
}


void exit_function()
{
  print_last_5_entries();
}

void exit_app()
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
