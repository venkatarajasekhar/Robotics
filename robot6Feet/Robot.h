
#ifndef ROBOT_H
#define ROBOT_H


#include "ServoController.h"
#include "RobotFoot.h"

class Robot {
protected:
  ServoController* svoController;
  RobotFoot* feet[6];
  boolean step;
  
public:
  Robot(ServoController* ctrl);

  ~Robot();
  
  void forward();

  void init();
};


#endif
