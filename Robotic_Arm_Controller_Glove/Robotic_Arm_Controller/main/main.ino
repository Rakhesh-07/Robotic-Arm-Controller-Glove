/*
|--------------------------------------------------------------------------------------------------
| Programmers Name: Kevin Lin, 
|                   Rakhesh V. Dhamodaran
| Course:           EECE-488 Senior Project I and II
| Program Name:     ECD526 Senior Capstone Project - Glove Controller
| Date:             09/2025 - 05/2025
|--------------------------------------------------------------------------------------------------
| Program Description:
|   This program is the software for the glove controller side of the project.
|   It takes the flex sensor values and ICM-20948 readings, processes them and sends them
|	  through BLE to the client side which is the Integrated Test Adapter. A few changes need to
|   be made in order to integrate with the mechanical arm (adjust motor values and add 
|   motor writes for the fingers)
|   Refer to the README.md file for library dependencies
|--------------------------------------------------------------------------------------------------
| Inputs:
|   Flex Sensor readings, accelerometer and gyroscope readings
|   
|--------------------------------------------------------------------------------------------------
| Outputs:
|   Output pitch, yaw, roll, and flex sensor voltage values through BLE to client side wirelessly
|   
|--------------------------------------------------------------------------------------------------
*/
#include "BLEServerPackage.h"
#include "ICM20948_Filter.h"
#include "FlexSensorReader.h"

//Define pins for Flex Sensors
#define Flex_Pin_1 33 //GPIO 33
#define Flex_Pin_2 34 //GPIO 34
#define Flex_Pin_3 35 //GPIO 35
#define Flex_Pin_4 25 //GPIO 25

// Initialize ICM, flexReader, and BLE
ICM20948Filter icmFilter;
FlexSensorReader flexReader(Flex_Pin_1, Flex_Pin_2, Flex_Pin_3, Flex_Pin_4);
BLEServerPackage bleServer;

void setup() {
  flexReader.begin(); // Initialize flexReader

  bleServer.begin(); // Initialize BLE Server

  Serial.begin(115200);
  if(!icmFilter.begin()) {
    Serial.println("ICM initialization failed!"); // Ensure proper connection SDA to SDA and SCL to SCL
    // Test with alternative ICM if issue persists
    while(1);
  }
  Serial.println("ICM initialization success!");
}

void loop() {
  icmFilter.update(); // update ICM20948 sensor data
  flexReader.readSensors(); // update flex sensor readings
  
  //Read roll, pitch, and yaw
  float roll = icmFilter.getRoll();
  float pitch = icmFilter.getPitch();
  float yaw = icmFilter.getYaw();

  //Convert roll, pitch, and yaw to string values
  String roll_str = String(roll);
  String pitch_str = String(pitch);
  String yaw_str = String(yaw);

  //Read Flex Sensors Values
  int sensor1 = flexReader.getSensor1Value();
  int sensor2 = flexReader.getSensor2Value();
  int sensor3 = flexReader.getSensor3Value();
  int sensor4 = flexReader.getSensor4Value();

  //Convert Flex Sensor Values to String
  String sensor1_str = String(sensor1);
  String sensor2_str = String(sensor2);
  String sensor3_str = String(sensor3);
  String sensor4_str = String(sensor4);

  // Define the array of values dynamically in main
  const char* messages[] = { sensor1_str.c_str(), sensor2_str.c_str(), sensor3_str.c_str(), sensor4_str.c_str(), roll_str.c_str(), pitch_str.c_str(), yaw_str.c_str() }; //converting string to constant char values for BLE

  uint8_t numStrings = sizeof(messages) / sizeof(messages[0]);

  // Send data over BLE to client
  bleServer.sendData(messages, numStrings);

  delay(50); // delay before sending next data
}
