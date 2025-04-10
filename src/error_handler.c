#include "error_handler.h"

int check_light_power(double light_power_value)
{
    if (light_power_value == 0)
    {
        logger(ERROR, "Light sensor Null: %lf\n", light_power_value);
        logger(ERROR, "Light: Possible disconnection at sensor end\n");
        return NOT_OK;
    }
    else if (light_power_value < 15)
    {
        logger(ERROR, "Light sensor Low: %lf\n", light_power_value);
        logger(ERROR, "Light: Possible overload circuit or short circuit\n");
        return NOT_OK;
    }
    else if (light_power_value > 25)
    {
        logger(ERROR, "Light sensor High: %lf\n", light_power_value);
        logger(ERROR, "Light: Possible worn out of the insulation, power surge or ground fault\n");
        return NOT_OK;
    }
    return OK;
}

int check_fan_power(double fan_power_value)
{
    if (fan_power_value == 0)
    {
        logger(ERROR, "Fan sensor NULL: %lf\n", fan_power_value);
        logger(ERROR, "Fan: Possible disconnection at sensor end\n");
        return NOT_OK;
    }
    else if (fan_power_value < 60)
    {
        logger(ERROR, "Fan sensor Low: %lf\n", fan_power_value);
        logger(ERROR, "Fan: Possible overload circuit or short circuit\n");
        return NOT_OK;
    }
    else if (fan_power_value > 80)
    {
        logger(ERROR, "Fan sensor High: %lf\n", fan_power_value);
        logger(ERROR, "Fan: Possible worn out of the insulation, power surge or ground fault\n");
        return NOT_OK;
    }
    return OK;
}

int check_ac_power(double ac_power_value)
{
    if (ac_power_value == 0)
    {
        logger(ERROR, "AC sensor Null: %lf\n", ac_power_value);
        logger(ERROR, "AC: Possible disconnection at sensor end\n");
        return NOT_OK;
    }
    else if (ac_power_value < 800)
    {
        logger(ERROR, "AC sensor Low: %lf\n", ac_power_value);
        logger(ERROR, "AC: Possible overload circuit or short circuit\n");
        return NOT_OK;
    }
    else if (ac_power_value > 1800)
    {
        logger(ERROR, "AC sensor High: %lf\n", ac_power_value);
        logger(ERROR, "AC: Possible worn out of the insulation, power surge or ground fault\n");
        return NOT_OK;
    }
    return OK;
}
