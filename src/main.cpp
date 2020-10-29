/*******************************************
 * Created by Cameron Sharp from team 10523, the Dragons
 *  
 * Pin Layout:
 *  transistor1 = 3;
 *  relay1 =8, 9;
 *  transistor2 = 10;
 *  relay2 = 11,12;
 *  
 *  front button = 2
 *  left button = 4
 *  right button = 7
 *  
 * Decimal input assignment:
 *  0 : stops left motor
 *  1 : stops right motor
 *  
 *  6-67 : reverse left motor
 *  68-129 : forward left motor
 *  
 *  131-191: forward right motor
 *  193-253: reverse right motor
 *******************************************/
#include "SoftwareSerial.h"
#include "Arduino.h"
#include "Printer.h"
#include "motorControl.h"
#include "dataRelay.h"

unsigned int timer;
int timerReset;
boolean buttonControl = false;

boolean dir8 = false;
boolean dir11 = false;

SoftwareSerial bt(hcRXPin, hcTXPin);
Printer print(&Serial, &bt);
dataRelay dr(&print);
motorControl mc(&dr.m1, &dr.m2);
void setUpPins();

void setup(){
  print.begin();
  
  setUpPins();

  timerReset = millis();

  delay(1000);
  digitalWrite(debugLED, HIGH);
  print.out("System Ready");
}

void loop(){
  timer = millis() - timerReset;

  if(bt.available()){
    buttonControl = false;
    timerReset = millis();
    int data = bt.read();
    dr.formatData(data);
  }
  else if(Serial.available() > 0){
    String data = Serial.readString();

    if(data == "debug"){
      dr.formatData(debugNumber);
    }
  }
  else if(timer > 500){
    if(!buttonControl)mc.stop();
     buttonControl = true;

    int front = digitalRead(PIN_FRONT);
    int left = digitalRead(PIN_LEFT) * 2;
    int right = digitalRead(PIN_RIGHT) * 4;

    int power = front + left + right;

    if(dr.debug && power != 0){
      print.out((String)power);
    }
    
    switch (power)
    {
      case 1:
        mc.moveMotors(FORWARD);
        break;
      case 2:
        mc.moveMotors(LEFT);
        break;
      case 4:
        mc.moveMotors(RIGHT);
        break;
      default:
        mc.stop();
        break;
    }
  }
}


void setUpPins(){
    pinMode(motor1Relay1, OUTPUT);
    pinMode(motor1Relay2, OUTPUT);
    pinMode(motor1Speed, OUTPUT);
    pinMode(motor2Relay1, OUTPUT);
    pinMode(motor1Relay2, OUTPUT);
    pinMode(motor2Speed, OUTPUT);
    pinMode(debugLED, OUTPUT);
};

