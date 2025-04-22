from flask import Flask, render_template, request, jsonify, url_for
import sqlite3
import os
from datetime import datetime
from collections import defaultdict

app = Flask(__name__)

# Constants
DB_FILE = "./smart_home.db"
CONTROL_PIPE = "/tmp/smart_home_ctrl"

# Sensor definitions
SENSORS = {
    1001: {"name": "Light", "icon": "light.png"},
    1002: {"name": "Fan", "icon": "fan.png"},
    1003: {"name": "AC", "icon": "ac.png"}
}

def create_device_state_table():
    conn = sqlite3.connect(DB_FILE)
    c = conn.cursor()
    c.execute("""
        CREATE TABLE IF NOT EXISTS device_states (
            device_id INTEGER PRIMARY KEY,
            state TEXT NOT NULL
        )
    """)
    conn.commit()
    conn.close()

def get_device_state(device_id):
    conn = sqlite3.connect(DB_FILE)
    c = conn.cursor()
    c.execute("SELECT state FROM device_states WHERE device_id=?", (device_id,))
    state = c.fetchone()
    conn.close()
    return state[0] if state else "off"  # default state is off

def set_device_state(device_id, state):
    conn = sqlite3.connect(DB_FILE)
    c = conn.cursor()
    c.execute("""
        INSERT INTO device_states (device_id, state)
        VALUES (?, ?)
        ON CONFLICT(device_id) DO UPDATE SET state = ?
    """, (device_id, state, state))
    conn.commit()
    conn.close()

def get_peak_usage_data(device_id):
    import sqlite3
    from datetime import datetime
    from collections import defaultdict

    conn = sqlite3.connect(DB_FILE)
    c = conn.cursor()

    try:
        c.execute("""
            SELECT timestamp, power_consumption
            FROM power_readings
            WHERE device_id = ?
            AND timestamp IS NOT NULL
            AND power_consumption IS NOT NULL
            ORDER BY timestamp DESC
        """, (device_id,))
        records = c.fetchall()
    except Exception as e:
        conn.close()
        print(f"Error fetching peak data: {e}")
        return [], []

    conn.close()

    # Aggregate usage by (date, hour)
    hourly_usage = defaultdict(float)

    for timestamp, power in records:
        try:
            ts_obj = datetime.strptime(timestamp, "%Y-%m-%d %H:%M:%S")
            key = (ts_obj.strftime("%b %d"), ts_obj.hour)  # e.g. ('Apr 22', 14)
            hourly_usage[key] += power
        except Exception as e:
            print(f"Skipping bad data row: {timestamp}, {power} — {e}")
            continue

    # Sort and format the output
    sorted_keys = sorted(hourly_usage)
    labels = [f"{day} {hour}:00" for day, hour in sorted_keys]
    values = [round(hourly_usage[key], 2) for key in sorted_keys]

    return labels, values


def get_sensor_data(device_id):
    conn = sqlite3.connect(DB_FILE)
    c = conn.cursor()

    c.execute("SELECT power_consumption FROM power_readings WHERE device_id=? ORDER BY id DESC LIMIT 1", (device_id,))
    current = c.fetchone()
    current = round(current[0], 2) if current else 0.0

    c.execute("SELECT AVG(power_consumption) FROM (SELECT power_consumption FROM power_readings WHERE device_id=? ORDER BY id DESC LIMIT 5)", (device_id,))
    avg = c.fetchone()
    avg = round(avg[0], 2) if avg and avg[0] else 0.0

    c.execute("SELECT MAX(power_consumption) FROM power_readings WHERE device_id=?", (device_id,))
    max_val = c.fetchone()
    max_val = round(max_val[0], 2) if max_val and max_val[0] else 0.0

    conn.close()
    return {"current": current, "avg": avg, "max": max_val}

def get_monthly_data(device_id):
    conn = sqlite3.connect(DB_FILE)
    c = conn.cursor()

    c.execute("""
        SELECT timestamp, power_consumption
        FROM power_readings
        WHERE device_id = ?
        AND timestamp >= datetime('now', '-30 days')
        ORDER BY timestamp ASC
    """, (device_id,))

    results = c.fetchall()
    conn.close()

    day_data = {}

    for row in results:
        ts = row[0]
        power_consumption = row[1]

        ts_obj = datetime.strptime(ts, "%Y-%m-%d %H:%M:%S")
        day = ts_obj.strftime("%Y-%m-%d")

        if day not in day_data:
            day_data[day] = []
        
        day_data[day].append(power_consumption)

    if len(day_data) == 1:
        return [{"time": row[0], "value": row[1]} for row in results[-5:]]

    averaged_data = []
    for day, values in day_data.items():
        avg_value = sum(values) / len(values)
        averaged_data.append({
            "time": day,
            "value": round(avg_value, 2)
        })

    return averaged_data

@app.route("/")
def index():
    sensor_data = {}
    device_states = {}

    for device_id in SENSORS:
        sensor_data[device_id] = get_sensor_data(device_id)
        device_states[device_id] = get_device_state(device_id)  # Assuming this function returns 'on' or 'off'

    return render_template(
        "index.html",
        sensors=SENSORS,
        data=sensor_data,
        device_states=device_states
    )


@app.route("/toggle", methods=["POST"])
def toggle():
    device_id = int(request.json.get("device_id"))
    state = request.json.get("state")  # true or false
    command = None

    # Set the state in the database
    set_device_state(device_id, "on" if state else "off")

    if device_id in SENSORS:
        if device_id == 1001:
            command = "light_on" if state else "light_off"
        elif device_id == 1002:
            command = "fan_on" if state else "fan_off"
        elif device_id == 1003:
            command = "ac_on" if state else "ac_off"

    if command:
        try:
            with open(CONTROL_PIPE, "w") as pipe:
                pipe.write(command + "\n")
            return jsonify({"status": "success", "command": command})
        except Exception as e:
            return jsonify({"status": "error", "message": str(e)})

    return jsonify({"status": "error", "message": "Invalid device ID"})

@app.route("/sensor/<int:device_id>")
def show_sensor_detail(device_id):
    if device_id not in SENSORS:
        return "Invalid device", 404

    graph_data = get_monthly_data(device_id)
    summary = get_sensor_data(device_id)
    sensor = SENSORS[device_id]
    device_state = get_device_state(device_id)

    # Parse monthly graph data
    graph_labels = [entry['time'] for entry in graph_data if entry['time']]
    graph_values = [entry['value'] for entry in graph_data if entry['value'] is not None]

    if not graph_labels or not graph_values:
        graph_labels = ["No data available"]
        graph_values = [0]

    # ✅ Add peak usage hourly data
    peak_labels, peak_values = get_peak_usage_data(device_id)

    return render_template(
        "sensor_detail.html",
        sensor=sensor,
        device_id=device_id,
        data=summary,
        graph_labels=graph_labels,
        graph_values=graph_values,
        device_state=device_state,
        peak_labels=peak_labels,
        peak_values=peak_values
    )


def create_control_pipe():
    if not os.path.exists(CONTROL_PIPE):
        try:
            os.mkfifo(CONTROL_PIPE)
            print(f"Created control pipe at {CONTROL_PIPE}")
        except Exception as e:
            print(f"Failed to create control pipe: {e}")

if __name__ == '__main__':
    create_device_state_table()  # Ensure the table is created at the start
    create_control_pipe()
    app.run(debug=True, host='0.0.0.0', port=5000)
