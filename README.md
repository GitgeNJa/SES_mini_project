# SES_mini_project
Simple C application that reads values from three sensors (mocked)
Analyses the data and display it in web server
Debug by using log at helper/smart_home.log

# Prerequisite 
* Linux command line
* gcc, make, python3
* Flask, SQlite (libsqlite3-dev)

## Commands
### get into the project folder
`cd .../SES_mini_project`
### make the binary
`make clean`
`make`
### start the application
`./smart`
### in a separate terminal view the latest logs
`tail -f helper/smart_home.log`
### Run the python script
`python3 smart_app_server.py`
### Access the webserver
* http://localhost:5000
* http://localhost:5000/sensor/1001
* http://localhost:5000/sensor/1002
* http://localhost:5000/sensor/1003
