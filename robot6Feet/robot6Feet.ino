#include "Robot.h"
#include <ServoDIY24.h>
#include <IRRemoteDIY.h>
#include <IRRemoteNECRecv.h>
#include <IRRemoteRecv.h>
#include <IRremote.h>

ServoDIY24 controller;
IRRemoteDIY remote(11);

Robot robot(&controller);

void setup() {
  Serial.begin(115200);
  while(!Serial) {
  }
  
  robot.stand();
  remote.enable();
}


void loop() {
  long key;
  if(remote.read(&key)) {
    if(key == IRRemoteDIY::KEY_PLUS) 
      robot.move(true);
    else if(key == IRRemoteDIY::KEY_MINUS) 
      robot.move(false);
    else if(key == IRRemoteDIY::KEY_C) 
      robot.stand();
  }
}
