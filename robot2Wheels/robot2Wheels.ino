
#include "Motor.h"
#include "GyroMPU6050.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include <Wire.h>
#include <PID_v1.h>
#include <math.h>
#include <String.h>
#include <LCD5110_Graph.h>
#include <StringFormat.h>
#include <PID_AutoTune_v0.h>

GyroMPU6050 gyro;

double stable =0.0 , input, output;
double kp=1,ki=0.5,kd=9;
double aTuneStep=100, aTuneNoise=10, aTuneStartValue=255;
unsigned int aTuneLookBack=20;
byte ATuneModeRemember=2;
unsigned long debugTime = 0;

Motor m1(6, 7), m2(5, 4);

PID pid( &input, &output, &stable, kp, ki, kd,  REVERSE);
PID_ATune aTune(&input, &output);

LCD5110 myGLCD(8,9,10,11,12);

boolean tuning = false;

extern uint8_t SmallFont[];


void changeAutoTune()
{
  if(!tuning)
  {
    //Set the output to the desired starting frequency.
    output=aTuneStartValue;
    aTune.SetNoiseBand(aTuneNoise);
    aTune.SetOutputStep(aTuneStep);
    aTune.SetLookbackSec((int)aTuneLookBack);
    AutoTuneHelper(true);
    tuning = true;
  }
  else
  { //cancel autotune
    aTune.Cancel();
    tuning = false;
    AutoTuneHelper(false);
  }
}

void AutoTuneHelper(boolean start)
{
  if(start)
    ATuneModeRemember = pid.GetMode();
  else
    pid.SetMode(ATuneModeRemember);
}

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
  Wire.begin();
  gyro.init();

  pid.SetMode(AUTOMATIC);
  pid.SetOutputLimits(-255, 255);

  if(tuning) {
    tuning=false;
    changeAutoTune();
    tuning=true;
  }

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

  int powerL = min(255, output + 45);
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

  Motion6T m6;
  gyro.readMotion6(m6);
    

  input = atan2(m6.ay, m6.az) * 180 / 3.1415926 - 2.0 ;

  if(input < -45 || input > 45) {
    //drive(0);
    //Serial.println(input);
    //Serial.println("\tfall down.");
    //delay(1000);
    return;
  }

  if(tuning)
  {
    byte val = (aTune.Runtime());
    if (val!=0)
    {
      tuning = false;
    }

    if(!tuning)
    { //we're done, set the tuning parameters
      kp = aTune.GetKp();
      ki = aTune.GetKi();
      kd = aTune.GetKd();
      pid.SetTunings(kp,ki,kd);
      AutoTuneHelper(false);
      Serial.println("done");
      display("Tuned!", 0);
    }
  }
  else {
    pid.Compute();
  }

  if(millis() > debugTime) {
    Serial.print(kp);
    Serial.print("\t -->\t");
    Serial.print(ki);
    Serial.print("\t -->\t");
    Serial.print(kd);
    Serial.print("\t     ||     \t");
    Serial.print(input);
    Serial.print("\t -->\t");
    Serial.print(stable);
    Serial.print("\t -->\t");
    Serial.print(output);
    //Serial.print(", ");
    //Serial.print(output - 255);
    if(tuning)
      Serial.println("\ttuning.");
    else
      Serial.println("\tdone.");

    debugTime += 100;
  }

 // drive(output - 255);
  drive(-output);
  delay(10);
  drive(0);
}



