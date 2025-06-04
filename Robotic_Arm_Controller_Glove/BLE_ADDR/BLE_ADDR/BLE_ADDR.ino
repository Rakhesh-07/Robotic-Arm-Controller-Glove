#include <BLEDevice.h>

void setup() {
  Serial.begin(115200);
  BLEDevice::init("ESP32-BLE-Server");
  
  Serial.print("BLE Server Address: ");
  Serial.println(BLEDevice::getAddress().toString().c_str());
}

void loop() {
  // Nothing needed here
}
