from flask import Flask, render_template

app = Flask(__name__)

def read_light_sensor_log():
    try:
        with open("./helper/light.txt", "r") as file:
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
        with open("./helper/fan.txt", "r") as file:
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
        with open("./helper/ac.txt", "r") as file:
            lines = file.readlines()
            value = float(lines[-1].strip())
            return [f"{value:.2f}"]
    except FileNotFoundError:
        return ["No AC sensor data found!"]
@app.route('/ac')
def index_ac():
    ac_value = read_ac_sensor_log()
    return render_template("index_ac.html", data=ac_value)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
