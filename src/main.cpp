#include <Arduino.h>
#include "BluetoothSerial.h"

//Next check if bluetooth is properly enabled by the board

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run "make menuconfig" to and enable it 
#endif

//create an instance of bluetooth seial
BluetoothSerial SerialBT;

#define ignition 13
#define starter 2
#define safety 23


void setup() {
Serial.begin(115200);
SerialBT.begin("ESP32 Bluetooth");
Serial.println("The device started, now you can pair it with bluetooth!");

pinMode(ignition,OUTPUT);
pinMode(starter,OUTPUT);
pinMode(safety, OUTPUT);

digitalWrite(safety,LOW);

}

void loop() {

  if (SerialBT.available()) {
    char data=SerialBT.read();
    
    
    if(data>=32 && data<=126){
      Serial.write(data); // this is for the serial monitor 
    }
  


    switch(data){
      case 'X':
        digitalWrite(safety,HIGH);
        break;

      case 'x':
        digitalWrite(safety,LOW);
        break;        

      case 'W':
        digitalWrite(ignition,HIGH);
        break;

      case 'w':
        digitalWrite(ignition,LOW);
        break;
 
      case 'F':
        if(digitalRead(safety)==LOW){
          digitalWrite(starter,HIGH);
          delay(500);
          digitalWrite(starter,LOW);
          delay(1000);
        }
        break;

        case 'B':
        if(digitalRead(safety)==LOW){
        digitalWrite(starter,HIGH);
        delay(700);
        digitalWrite(starter,LOW);
        delay(1000);
        }
        break;

        case 'L':
        if(digitalRead(safety)==LOW){
        digitalWrite(starter,HIGH);
        delay(900);
        digitalWrite(starter,LOW);
        delay(1000);
        }
        break;

        case 'R':
        if(digitalRead(safety)==LOW){
        digitalWrite(starter,HIGH);
        delay(1100);
        digitalWrite(starter,LOW);
        delay(1000);
        }
        break;
    }
  }
  delay(2);
}