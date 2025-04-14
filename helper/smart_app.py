from flask import Flask, render_template

app = Flask(__name__)

def read_light_sensor_log():
    try:
        with open("../helper/light_sensor_value.txt", "r") as file:
            lines = file.readlines()
            value = float(lines[-1].strip())
            return [f"{value:.2f}"]
    except FileNotFoundError:
        return ["No light sensor data found!"]
@app.route('/light')
def index_light():
    light_value = read_light_sensor_log()
    return render_template("index_light.html", data=light_value)

def read_fan_sensor_log():
    try:
        with open("../helper/fan_sensor_value.txt", "r") as file:
            lines = file.readlines()
            value = float(lines[-1].strip())
            return [f"{value:.2f}"]
    except FileNotFoundError:
        return ["No fan sensor data found!"]
@app.route('/fan')
def index_fan():
    fan_value = read_fan_sensor_log()
    return render_template("index_fan.html", data=fan_value)

def read_ac_sensor_log():
    try:
        with open("../helper/ac_sensor_value.txt", "r") as file:
            lines = file.readlines()
            value = float(lines[-1].strip())
            return [f"{value:.2f}"]
    except FileNotFoundError:
        return ["No AC sensor data found!"]
@app.route('/ac')
def index_ac():
    ac_value = read_ac_sensor_log()
    return render_template("index_ac.html", data=ac_value)

####################################################################################################

def compute_sensor_stats(filepath):
    try:
        with open(filepath, "r") as file:
            lines = file.readlines()
            if not lines:
                return None

            last_five_lines = lines[-5:]
            readings = []
            for line in last_five_lines:
                try:
                    reading = float(line.strip())
                    readings.append(reading)
                except ValueError:
                    continue
            if not readings:
                return None

            avg = sum(readings) / len(readings)
            low = min(readings)
            high = max(readings)
            return avg, low, high
    except FileNotFoundError:
        return None

@app.route('/light_stats')
def index_light_stats():
    stats = compute_sensor_stats("../helper/light_sensor_value.txt")
    if stats is None:
        data = "No valid sensor data found."
    else:
        avg, low, high = stats
        data = {
            "average": f"{avg:.2f}",
            "lowest": f"{low:.2f}",
            "highest": f"{high:.2f}"
        }
    return render_template("index_light_stats.html", data=data)

@app.route('/fan_stats')
def index_fan_stats():
    stats = compute_sensor_stats("../helper/fan_sensor_value.txt")
    if stats is None:
        data = "No valid sensor data found."
    else:
        avg, low, high = stats
        data = {
            "average": f"{avg:.2f}",
            "lowest": f"{low:.2f}",
            "highest": f"{high:.2f}"
        }
    return render_template("index_fan_stats.html", data=data)

@app.route('/ac_stats')
def index_ac_stats():
    stats = compute_sensor_stats("../helper/ac_sensor_value.txt")
    if stats is None:
        data = "No valid sensor data found."
    else:
        avg, low, high = stats
        data = {
            "average": f"{avg:.2f}",
            "lowest": f"{low:.2f}",
            "highest": f"{high:.2f}"
        }
    return render_template("index_ac_stats.html", data=data)

####################################################################################################

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
