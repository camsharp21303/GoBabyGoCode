#include <Arduino.h>
#include <SoftwareSerial.h>
#include <math.h>

#define PIN_FRONT 2
#define PIN_LEFT 4
#define PIN_RIGHT 7

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

unsigned int timer;
int timerReset;

boolean dir8 = false;
boolean dir11 = false;

boolean debug = false;

SoftwareSerial bt(6, 5);

void blink();

void printer(String message){
  Serial.println(message);
  bt.println(message);
}

void formatData(int d);

void setup(){
  Serial.begin(9600);
  bt.begin(9600);

  pinMode(3, OUTPUT);

  for(int i = 8; i < 14; i++){
    pinMode(i, OUTPUT);
  }

  pinMode(PIN_FRONT, INPUT);
  pinMode(PIN_LEFT, INPUT);
  pinMode(PIN_RIGHT, INPUT);
  timerReset = millis();

  delay(1000);
  digitalWrite(13, HIGH);
  printer("System Ready");
}

void loop(){
  timer = millis() - timerReset;

  if(bt.available()){
    timerReset = millis();
    int data = bt.read();
    formatData(data);
  }
  else if(Serial.available()){
    int data = Serial.read();
     Serial.println(data);

    switch (data)
    {
    case 2:
      while(!Serial.available()){
        formatData(78);
      }
      break;
    
    default:
      formatData(data);
      break;
    }
  }
  else if(timer > 500){
    formatData(0);
    formatData(1);

    int front = digitalRead(PIN_FRONT);
    int left = digitalRead(PIN_LEFT) * 2;
    int right = digitalRead(PIN_RIGHT) * 4;

    int power = front + left + right;

    if(debug){
      printer((String)power);
    }
    
    switch (power)
    {
      case 1:
        digitalWrite(8, HIGH);
        digitalWrite(9, LOW);
        digitalWrite(11, HIGH);
        digitalWrite(12, LOW);
        analogWrite(3, 100);
        analogWrite(10, 100);
        break;
      case 2:
        digitalWrite(8, HIGH);
        digitalWrite(9, LOW);
        digitalWrite(11, LOW);
        digitalWrite(12, HIGH);
        analogWrite(3, 100);
        analogWrite(10, 100);
        break;
      case 4:
        digitalWrite(8, LOW);
        digitalWrite(9, HIGH);
        digitalWrite(11, LOW);
        digitalWrite(12, HIGH);
        analogWrite(3, 100);
        analogWrite(10, 100);
        break;
      default:
        formatData(0);
        formatData(1);
        break;
    }

  }
}
void blink(){
  for(int i = 0; i < 3; i++){
    digitalWrite(13, LOW);
    delay(50);
    digitalWrite(13, HIGH);
    delay(500);
  }
}

void formatData(int d){
  switch (d)
  {
  case 0:
    digitalWrite(3, LOW);
    break;
  case 1:
    digitalWrite(10, LOW);
    break;
  case 3:
    if(debug){
      debug = false;
      blink();
      printer("Debugging is off");
    }
    else{
      debug  = true;
      blink();
      printer("Debugging is on");
    }
    break;
  default:
    int pin1 = atan(2*d-260)+10;
    int pin2 = pin1 + 1;
    int pin3 = 3;

    if(pin2 == 12){
      pin3 = 10;
    }

    int dirV = -pow(d-131,2)/46 + 84;
    boolean dir = false;
    if(dirV >= 0){
      dir = true;
    }
    int power = (d-6)%62;

    if(debug){
      printer((String)pin1 + "   " + (String)pin2 + "   " + (String)pin3 + "   " + d + "   " + power);
    }

    switch (pin1){
      case 8:
        if(dir8 != dir){
          analogWrite(pin3, 0);
          if(digitalRead(pin1) == 1){

            digitalWrite(pin2, true);
          }
          else{
            digitalWrite(pin2, false);
            digitalWrite(pin1, true);
          }
          analogWrite(pin3, power*4);
        }
        dir8 = dir;
        break;
      case 11:
        if(dir11 != dir){
          analogWrite(pin3, 0);
          if(digitalRead(pin1) == 1){
            digitalWrite(pin1, false);
            digitalWrite(pin2, true);
          }
          else{
            digitalWrite(pin2, false);
            digitalWrite(pin1, true);
          }
          
          analogWrite(pin3, power*4);
        }
        dir11 = dir;
        break;
    }
    digitalWrite(pin1, dir);
    digitalWrite(pin2, !dir);
    analogWrite(pin3, power*4);
    break;
  }
}