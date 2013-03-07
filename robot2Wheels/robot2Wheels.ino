
#include "Motor.h"
#include "GyroMPU6050.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include <Wire.h>

GyroMPU6050 gyro;
float stable = 0.0;

Motor m1(6, 7), m2(4, 5);
  
  
void setup() {
  Serial.begin(9600);
  Wire.begin();
  gyro.init();
  
  digitalWrite(13, 1);
  
  delay(2000);
  
  EulerT el;
  while(true) {
    if(gyro.readEuler(el))
      break;
  }
  stable = el.theta;
  digitalWrite(13, 0);
}

void loop() {
  
  EulerT el;
  while(!gyro.readEuler(el));
  
  Serial.print(el.theta);
  Serial.print("\t -->\t");
  Serial.println(stable);
  
  if((el.theta) < stable) {
     m1.forward(40);
     m2.forward(40);
  }
  else if((el.theta) > stable) {
     m1.back(40);
     m2.back(40);
  }
  //delay(10);
  //m1.brake();
 // m2.brake();
  //delay(10);
}
