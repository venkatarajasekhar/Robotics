#include "Robot.h"
#include "Servo24.h"

Servo24 controller;
Robot robot(&controller);

void setup() {
  Serial.begin(115200);
  while(!Serial) {
  }
  
  robot.init();
}


void loop() {
   robot.forward();
}
