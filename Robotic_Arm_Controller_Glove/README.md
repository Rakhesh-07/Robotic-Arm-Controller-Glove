**ECD526 Senior Capstone Project**
Robotic Arm Controller 
2024-2025

Description
This project is a collaborative capstone project between ECE and ME students to create a glove-based controller for a robotic arm. 
Inspired by the NES Power Glove, the goal is to enable users to manipulate a robotic hand and arm in real time using natural hand gestures. 
The controller is designed for public use at the TechWorks! museum in Binghamton, NY.


This software is written on the Arduino IDE 2.3.5
Board Manager:
esp32 by Expressif Systems - https://github.com/espressif/arduino-esp32

Library Manager:
Adafruit ICM20X by Adafruit - https://github.com/adafruit/Adafruit_ICM20X
ESP32AnalogRead by Kevin Harrington - https://github.com/madhephaestus/ESP32AnalogRead
ESP32Servo by Kevin Harrington, John K. Bennett - https://madhephaestus.github.io/ESP32Servo/annotated.html

Potential Requirements (A lot of testing for old stuff that may or may not be needed)
Adafruit GFX Library by Adafruit
Adafruit Unified Sensor by Adafruit
SparkFun 9DoF IMU Breakout - ICM 20948 - https://github.com/sparkfun/SparkFun_ICM-20948_ArduinoLibrary


Installing
Install and extract the zip file from Senior Project Archives 2024-2025 ECD526
One folder contains:
- main.ino
- BLEServerPackage.cpp
- BLEServerPackage.h
- FlexSensorReader.cpp
- FlexSensorReader.h
- ICM20948_Filter.cpp
- ICM20948_Filter.h

The client folder contains:
- updated_client.ino

This is programmed on the ESP32 with Serial baud rate 115200
**CP210x_VCP_Windows may be required to detect the ESP32 on the COM port**


Any advise for common problems or issues.
-If ESP32 is not detectable by Arduino IDE - you may need to install the port detecter - CP210x_VCP_Windows
-If using a different ESP32 for the glove controller, update the client code with proper BLEAddress with the external file provided
-Double check pin connections with the provided schematic
-ESP32 may be fried if it can't be programmable
-MPU/ICM may be fried if it can't be detected when wired correctly
-Ensure proper ITA power (V on top, gorund on bottom)
-Ensure proper motor connection (ground on the left)


Authors
Rakhesh Varshan Dhamodaran - rdhamodaran@binghamton.edu
Kevin Lin - klin138@binghamton.edu
