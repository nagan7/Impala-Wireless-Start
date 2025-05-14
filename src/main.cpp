#include <Arduino.h>
#include "BluetoothSerial.h"

//Next check if bluetooth is properly enabled by the board

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run "make menuconfig" to and enable it 
#endif

//create an instance of bluetooth seial
BluetoothSerial SerialBT;


void setup() {
Serial.begin(115200);
SerialBT.begin("ESP32 Bluetooth");
Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (Serial.available()){
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  delay(20);
}