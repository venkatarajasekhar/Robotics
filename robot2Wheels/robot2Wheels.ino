
#include "Motor.h"
#include <PID_v1.h>
#include <math.h>
#include <String.h>
#include <LCD5110_Graph.h>
#include <StringFormat.h>


double stable =0.0 , input, output;
double targetPos;
unsigned long debugTime = 0;

//#define GYRO_MPU6050

#ifdef GYRO_MPU6050

#include "GyroMPU6050.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include <Wire.h>
GyroMPU6050 gyro;

double getTargetPos() {
  return 0.0;
}

double getInput() {
  Motion6T m6;
  gyro.readMotion6(m6);
  return (atan2(m6.ay, m6.az) * 180 / 3.1415926  - targetPos);
}

#else

double getAngle() {
  double x = analogRead(0);
  double z = analogRead(2);
  return (atan2(x, z) * 180 / 3.1415926);
}

double getTargetPos() {
  digitalWrite(13, 0);
  delay(2000);
  double ret =  getAngle();
  digitalWrite(13, 1);
  return ret;
}



double getInput() {
  double pos = getAngle();
  return (pos  - targetPos);
}

#endif



Motor m1(6, 7), m2(4, 5);

PID pid( &input, &output, &stable,  2, 0, 0,  REVERSE);

LCD5110 myGLCD(8,9,10,11,12);
extern uint8_t SmallFont[];

void display(char* s, int line = 0) {
  myGLCD.clrScr();
  myGLCD.print(s, 0, line * 16);
  myGLCD.update();
}


void setup() {
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);

  Serial.begin(9600);

  Serial.println("Initializing......");
  display("Initializing......");
  targetPos = getTargetPos();

  pid.SetMode(AUTOMATIC);
  pid.SetOutputLimits(-255, 255);
  pid.SetSampleTime(60);

  Serial.println("Ready!");
  display("Ready......");
}


void drive(double output) {
  bool forward = true;

  if(output < 0)
    forward = false;
  output = abs(output);

  if(output < 3) {
    m1.brake();
    m2.brake();
    return;
  }

  int powerL = min(255, output + 100);
  int powerR = powerL;

  if(forward) {
    m1.forward(powerL);
    m2.forward(powerR);
    //     Serial.print(powerL);
    //     Serial.println("\tforward");
  }
  else {
    m1.back(powerL);
    m2.back(powerR);
    //     Serial.print(powerL);
    //     Serial.println("\tback");
  }
  // delay(2); 
}

void loop() {
  input = getInput();

  /*if(input < -45 || input > 45) {
    drive(0);
    //Serial.println(input);
    //Serial.println("\tfall down.");
    //delay(1000);
    return;
  }*/

  pid.Compute();

 if(millis() > debugTime) {
    Serial.print(input);
    Serial.print("\t -->\t");
    Serial.print(stable);
    Serial.print("\t -->\t");
    Serial.println(output);

    debugTime += 100;
  }

  //drive(-output);
  delay(20);
  //drive(0);
}



