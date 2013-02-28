
#ifndef ROBOT_H
#define ROBOT_H


#include <ServoController.h>
#include "RobotFoot.h"

class Robot {
protected:
  ServoController* svoController;
  RobotFoot* feet[6];
  bool step;
  
public:
  Robot(ServoController* ctrl);

  ~Robot();
  
  void move(bool forward);
  
  void stand();
};


#endif
