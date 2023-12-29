#include <SoftwareSerial.h>

SoftwareSerial HC06(2, 3);
const int motorA1 = 5;
const int motorB1 = 6;
const int motorA2 = 9;
const int motorB2 = 10;
const int trig = 11;
const int echo = 12;

int mode = 0; 
int distance = 0;

void setup() {
  Serial.begin(9600);
  pinMode(motorA1, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
  while (!Serial) {
    ;
  }
  HC06.begin(9600);
}

long sr04(){
  long duration, distance;

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration * 17 / 1000;

  return duration;
}


void loop() {
  distance = sr04();
  Serial.println(distance);

  if (HC06.available()) {
    mode = HC06.read();
    Serial.println(mode);

    if (distance > 500){
      if(mode == 98){
        digitalWrite(motorA1, HIGH);
        digitalWrite(motorB1, LOW);
        digitalWrite(motorA2, HIGH);
        digitalWrite(motorB2, LOW);
        Serial.println(mode);
      }
      if(mode == 108){ // 좌
        digitalWrite(motorA1, LOW);
        digitalWrite(motorB1, HIGH);
        digitalWrite(motorA2, HIGH);
        digitalWrite(motorB2, LOW);
        Serial.println(mode);
      }
      if(mode == 114){ // 우
        digitalWrite(motorA1, HIGH);
        digitalWrite(motorB1, LOW);
        digitalWrite(motorA2, LOW);
        digitalWrite(motorB2, HIGH);
        Serial.println(mode);
      }
      if(mode == 102){ // 뒤
        digitalWrite(motorA1, LOW);
        digitalWrite(motorB1, HIGH);
        digitalWrite(motorA2, LOW);
        digitalWrite(motorB2, HIGH);
        Serial.println(mode);
      }
      if(mode == 115){
        digitalWrite(motorA1, LOW);
        digitalWrite(motorB1, LOW);
        digitalWrite(motorA2, LOW);
        digitalWrite(motorB2, LOW);
        Serial.println(mode);
      }
    }
  }
  if(distance < 300 && 0 < distance){
      digitalWrite(motorA1, 0);
      digitalWrite(motorB1, 0);
      digitalWrite(motorA2, 0);
      digitalWrite(motorB2, 0);
      Serial.println("stop");
  }
}
