#include "Motor.h"
#include <Arduino.h>

Motor::Motor(int pin1, int pin2) {
  this->pin1 = pin1;
  this->pin2 = pin2;    
}

void Motor::forward(int speed) {
  analogWrite(pin1, speed);
  analogWrite(pin2, 0);
}


void Motor::back(int speed) {
  analogWrite(pin2, speed);
  analogWrite(pin1, 0);
}

void Motor::brake() {
  analogWrite(pin2, 255);
  analogWrite(pin1, 255);
}



