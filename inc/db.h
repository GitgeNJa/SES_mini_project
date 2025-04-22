#ifndef DB_H
#define DB_H

#define OK 0
#define NOT_OK 1

// Function declarations for DB functionality
int initialize_database();
int write_light_power_value(double light_power_value);
int write_fan_power_value(double fan_power_value);
int write_ac_power_value(double ac_power_value);
void print_last_5_entries();
#endif // DB_H
