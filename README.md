# SES_mini_project
Simple C application that reads values from three different files using three threads at separate intervals
Logs them in smart_home.log in helper folder
Analyses the data and display it in local_host

# Prerequisite 
* Linux command line
* gcc, make, python3
* Flask

## Commands
get into the project folder
`cd .../SES_mini_project`
make the binary
`make clean`
`make`
start the application
`./smart`
in a separate terminal view the latest logs
`tail -f helper/smart_home.log`
Run the python script
`python3 smart_app.py` in flask
Use different endpoints to display different data structures
* http://localhost:5000/light
* http://localhost:5000/fan
* http://localhost:5000/ac
* http://localhost:5000/light_stats
* http://localhost:5000/fan_stats
* http://localhost:5000/ac_stats
