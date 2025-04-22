#include "error_handler.h"

/*
 * LIGHT CHECK:
 * Typical Indian LED/CFL bulbs run between 5W to 23W (at 230V).
 * We consider 15W–25W as a healthy operating window.
 * Below 15W => May indicate underload, miscalibration or faulty sensor.
 * Above 25W => Likely a short circuit, power surge, or internal fault.
 */
int check_light_power(double light_power_value)
{
    if (light_power_value == 0)
    {
        logger(ERROR, "Light sensor NULL: %lf\n", light_power_value);
        logger(ERROR, "Light: Possible disconnection at sensor end\n");
        return NOT_OK;
    }
    else if (light_power_value < 15)
    {
        logger(ERROR, "Light sensor LOW: %lf\n", light_power_value);
        logger(ERROR, "Light: Possible underload, fault, or sensor miscalibration\n");
        return NOT_OK;
    }
    else if (light_power_value > 25)
    {
        logger(ERROR, "Light sensor HIGH: %lf\n", light_power_value);
        logger(ERROR, "Light: Possible surge, overload or ground fault\n");
        return NOT_OK;
    }
    return OK;
}

/*
 * FAN CHECK:
 * Ceiling fans in Indian homes consume around 40W–70W depending on speed and type.
 * We accept 40W–70W as a valid operating range.
 * Below 40W => Might be under-voltage, stuck blades, or bad wiring.
 * Above 70W => Could indicate winding fault, surge, or motor issue.
 */
int check_fan_power(double fan_power_value)
{
    if (fan_power_value == 0)
    {
        logger(ERROR, "Fan sensor NULL: %lf\n", fan_power_value);
        logger(ERROR, "Fan: Possible disconnection at sensor end\n");
        return NOT_OK;
    }
    else if (fan_power_value < 40)
    {
        logger(ERROR, "Fan sensor LOW: %lf\n", fan_power_value);
        logger(ERROR, "Fan: Possible under-voltage or circuit issue\n");
        return NOT_OK;
    }
    else if (fan_power_value > 70)
    {
        logger(ERROR, "Fan sensor HIGH: %lf\n", fan_power_value);
        logger(ERROR, "Fan: Possible overcurrent, winding fault, or surge\n");
        return NOT_OK;
    }
    return OK;
}

/*
 * AC CHECK:
 * A 1-1.5 Ton Split AC in India usually draws between 900W to 1600W.
 * We're using 900W–1700W as our safe window.
 * Below 900W => May be due to gas leakage, low load, or faulty compressor.
 * Above 1700W => Indicates possible surge, compressor overload, or ground fault.
 */
int check_ac_power(double ac_power_value)
{
    if (ac_power_value == 0)
    {
        logger(ERROR, "AC sensor NULL: %lf\n", ac_power_value);
        logger(ERROR, "AC: Possible disconnection at sensor end\n");
        return NOT_OK;
    }
    else if (ac_power_value < 900)
    {
        logger(ERROR, "AC sensor LOW: %lf\n", ac_power_value);
        logger(ERROR, "AC: Possible gas leakage, overload circuit, or sensor fault\n");
        return NOT_OK;
    }
    else if (ac_power_value > 1700)
    {
        logger(ERROR, "AC sensor HIGH: %lf\n", ac_power_value);
        logger(ERROR, "AC: Possible insulation wear, surge, or load mismatch\n");
        return NOT_OK;
    }
    return OK;
}
