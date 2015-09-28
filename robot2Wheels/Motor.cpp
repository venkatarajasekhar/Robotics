#include "Motor.h"
#include <Arduino.h>

Motor::Motor(int pin1, int pin2) {
  try{
  this->pin1 = pin1;
  }catch(...){
    
  }
  try{
    this->pin2 = pin2;    
  }catch(...){
    
  }
}

void Motor::forward(int speed) {
  try{
  analogWrite(pin1, speed);
  }catch(...){
    
  }
  try{
    analogWrite(pin2, 0);
  }catch(...){
    
  }
}


void Motor::back(int speed) {
  try{
  analogWrite(pin2, speed);
  }catch(...){
    
  }
  try{
    analogWrite(pin1, 0);
  }catch(...){
    
  }
}

void Motor::brake() {
  try{
  analogWrite(pin2, 255);
  }catch(...){
    
  }
  try{
    analogWrite(pin1, 255);
  }catch(...){
    
  }
}



