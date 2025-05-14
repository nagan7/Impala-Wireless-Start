#include <Arduino.h>
#include "BluetoothSerial.h"

//Next check if bluetooth is properly enabled by the board

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run "make menuconfig" to and enable it 
#endif

//create an instance of bluetooth seial
BluetoothSerial SerialBT;

#define ignition 2
#define starter 4



void setup() {
Serial.begin(115200);
SerialBT.begin("ESP32 Bluetooth");
Serial.println("The device started, now you can pair it with bluetooth!");

pinMode(ignition,OUTPUT);
pinMode(starter,OUTPUT);

}

void loop() {

  if (SerialBT.available()) {
    char data=SerialBT.read();
    Serial.write(SerialBT.read()); // this is for the serial monitor 

    if(data=='W' ){
      digitalWrite(ignition,HIGH);
    }
    else if(data=='w'){
      digitalWrite(ignition,LOW);
    }
  }
  delay(1);
}