#include <Arduino.h>
#include "BluetoothSerial.h"

//Next check if bluetooth is properly enabled by the board

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run "make menuconfig" to and enable it 
#endif

//create an instance of bluetooth seial
BluetoothSerial SerialBT;

#define ignition 12
#define starter 13
#define safety 23

unsigned long last_start=0;
const unsigned long cooldown=2000;

void triggerStarter(unsigned int duration);


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
        triggerStarter(700);
        break;

        case 'B':
        triggerStarter(900);
        break;

        case 'L':
        triggerStarter(1100);
        break;

        case 'R':
        triggerStarter(1300);
        break;
    }
  }
  delay(2);
}



void triggerStarter(unsigned int duration){
  if(digitalRead(safety)==LOW){
    unsigned long current_time=millis();
    if(current_time-last_start>=cooldown){
        digitalWrite(starter,HIGH);
        delay(duration);
        digitalWrite(starter,LOW);
        last_start=millis();
        delay(1000);
    }
  }
}