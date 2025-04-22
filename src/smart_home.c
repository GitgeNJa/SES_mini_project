#include "smart_home.h"

int main()
{
    logger(ERROR, "\n\n\n");
    logger(ERROR, "Welcome to Smart Home\n");
    initialize_database();
    if (threading() == NOT_OK)
    {
        return NOT_OK;
    }
    exit_app();
    return OK;
}
