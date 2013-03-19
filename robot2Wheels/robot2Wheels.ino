
#include "Motor.h"
#include <PID_v1.h>
#include <math.h>
#include <String.h>
#include <LCD5110_Graph.h>
#include <StringFormat.h>


double stable =0.0 , input, output;
double targetPos;
unsigned long debugTime = 0;

#define GYRO_MPU6050

#ifdef GYRO_MPU6050

#include "GyroMPU6050.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include <Wire.h>
GyroMPU6050 gyro;


double getTargetPos() {
  Wire.begin();
  gyro.init();
  return 7.0;
}

double getInput() {
  int times = 20;
  
  double ret = 0.0;
  EulerT e;
  for(int i=0; i<times; ++i) {
    if(gyro.readEuler(e))
      ret += e.phi;
  }
  
  ret = ret / times;
  return ret - targetPos;
  
  /*
  double ay = 0.0, az = 0.0;
  Motion6T m6;
  for(int i=0; i<times; ++i) {
    gyro.readMotion6(m6);
    ay += m6.ay;
    az += m6.az;
  }
  
  ay = ay / times;
  az = az / times;
  
  return (atan2(ay, az) * 180 / 3.1415926  - targetPos);
  */
}

#else

double getAngle() {
  unsigned long rx = 0, rz = 0;
  for(int i=0; i<100; ++i) {
    rx += analogRead(0);
    rz += analogRead(2);
  }
  
  rx = rx  / 10;
  rz = rz / 10;
  
  double gx = map(rx , 2710, 7570, -10000, 10000) / 10000.0;
  double gz = map(rz, 1830, 6818, -10000, 10000) / 10000.0;
  
   return atan2(gx, gz) * 180 / 3.1415926;
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



Motor m1(6, 7), m2(5, 4);

PID pid( &input, &output, &stable,  4, 0, 0,  REVERSE);

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
  pid.SetSampleTime(5);

  Serial.println("Ready!");
  display("Ready......");
}


void drive(double output) {
  bool forward = true;

  if(output < 0)
    forward = false;
  output = abs(output);

 // if(output < 10) {
  //  m1.brake();
   // m2.brake();
   // return;
  //}

  int powerL = 255;// min(255, output + 155);
  int powerR = powerL;
// Serial.println(powerL);

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
  if(input == -1000.0)
    return;
    
//  drive(0);
  
  //if(abs(input) < 2) {
    //drive(0);
  //  return;
  //}

  if(input < -45 || input > 45) {
  //delay(20);
    return;
  }

  pid.Compute();

 if(millis() > debugTime) {
    Serial.print(input);
    Serial.print("\t -->\t");
    Serial.print(stable);
    Serial.print("\t -->\t");
    Serial.println(output);

    debugTime += 100;
  }

  drive(-output);
 // delay(10);
 // drive(0);
}



