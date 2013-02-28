#include <IRRemoteDIY.h>
#include <ServoDIY24.h>

#ifndef ROBOT6FEET_H
#define ROBOT6FEET_H 1

#include <ServoController.h>

class RobotFoot {
protected:
  int legSvo, kneeSvo, toeSvo;
  int legBaseAngle, kneeBaseAngle, toeBaseAngle;
  bool left;
  ServoController* svoController;
  
public:

  static const bool LEFT = true;
  static const bool RIGHT = false;

  RobotFoot(ServoController* ctrler, int legSv, int kneeSv, int toeSv, bool lft);
  
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

