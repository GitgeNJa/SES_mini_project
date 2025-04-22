#include <stdio.h>
#include <sqlite3.h>
#include "db.h"
#include "logger.h"
#include <pthread.h>

#define DB_FILE_NAME "./helper/smart_home.db"  // SQLite DB file path

static sqlite3 *db;  // SQLite database handle
static pthread_mutex_t db_mutex = PTHREAD_MUTEX_INITIALIZER;  // Mutex for DB synchronization

// Function to initialize the SQLite database
int initialize_database()
{
    int rc = sqlite3_open(DB_FILE_NAME, &db);  // Open SQLite database
    if (rc != SQLITE_OK)
    {
        logger(ERROR, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return NOT_OK;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS power_readings ("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                   "device_id INTEGER, "
                                   "timestamp TEXT, "
                                   "power_consumption REAL);";
    char *err_msg = 0;
    rc = sqlite3_exec(db, create_table_sql, 0, 0, &err_msg);  // Create table if it doesn't exist
    if (rc != SQLITE_OK)
    {
        logger(ERROR, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return NOT_OK;
    }

    return OK;
}

// Function to insert sensor reading into the database
int insert_sensor_reading(int device_id, double power_value)
{
    char time_buffer[64];
    get_time(time_buffer, sizeof(time_buffer));

    // Lock the database to prevent concurrent writes
    pthread_mutex_lock(&db_mutex);

    // Prepare SQL insert query
    const char *insert_sql = "INSERT INTO power_readings (device_id, timestamp, power_consumption) "
                             "VALUES (?, ?, ?);";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, 0);
    if (rc != SQLITE_OK)
    {
        logger(ERROR, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        pthread_mutex_unlock(&db_mutex);
        return NOT_OK;
    }

    // Bind parameters to the SQL query
    sqlite3_bind_int(stmt, 1, device_id);
    sqlite3_bind_text(stmt, 2, time_buffer, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, power_value);

    // Execute the query
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        logger(ERROR, "Execution failed: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        pthread_mutex_unlock(&db_mutex);
        return NOT_OK;
    }

    // Clean up
    sqlite3_finalize(stmt);

    // Unlock the database after the operation is complete
    pthread_mutex_unlock(&db_mutex);

    return OK;
}
void print_last_5_entries()
{
    const char *select_sql = "SELECT device_id, timestamp, power_consumption "
                             "FROM power_readings ORDER BY id DESC LIMIT 5;";

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, select_sql, -1, &stmt, 0);
    if (rc != SQLITE_OK)
    {
        logger(ERROR, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    int row_count = 0;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        int device_id = sqlite3_column_int(stmt, 0);
        const char *timestamp = (const char *)sqlite3_column_text(stmt, 1);
        double power_consumption = sqlite3_column_double(stmt, 2);

        // Print the results in a human-readable format
        printf("Entry %d:\n", ++row_count);
        printf("Device ID: %d\n", device_id);
        printf("Timestamp: %s\n", timestamp);
        printf("Power Consumption: %.2f Watts\n", power_consumption);
        printf("-----------------------------------\n");
    }

    if (rc != SQLITE_DONE)
    {
        logger(ERROR, "Failed to fetch rows: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
}

// Function to write light power value to the database (Device ID: 1001)
int write_light_power_value(double light_power_value)
{
    return insert_sensor_reading(1001, light_power_value);
}

// Function to write fan power value to the database (Device ID: 1002)
int write_fan_power_value(double fan_power_value)
{
    return insert_sensor_reading(1002, fan_power_value);
}

// Function to write AC power value to the database (Device ID: 1003)
int write_ac_power_value(double ac_power_value)
{
    return insert_sensor_reading(1003, ac_power_value);
}
