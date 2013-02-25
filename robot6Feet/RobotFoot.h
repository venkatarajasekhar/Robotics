#ifndef ROBOT6FEET_H
#define ROBOT6FEET_H 1

#include "ServoController.h"

class RobotFoot {
protected:
  int legSvo, kneeSvo, toeSvo;
  int legBaseAngle, kneeBaseAngle, toeBaseAngle;
  boolean left;
  ServoController* svoController;
  
public:

  static const boolean LEFT = true;
  static const boolean RIGHT = false;

  RobotFoot(ServoController* ctrler, int legSv, int kneeSv, int toeSv, boolean lft);
  
  void setBasePos(int legBaseAngle, int kneeBaseAngle, int toeBaseAngle) ;
  
  void kneePos(int kneeAngle);
  
  void toePos(int toeAngle);
    
  void legPos(int legAngle) ;
  
  void liftUp() ;
  
  void putDown() ;
  
  void forward() ;
  
  void back() ;
  
  void legBasePos();
  
  void kneeBasePos();
  
  void toeBasePos();
};

#endif

