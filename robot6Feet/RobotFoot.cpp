#include "Servo24.h"
#include "RobotFoot.h"

RobotFoot::RobotFoot(ServoController* ctrler, int legSv, int kneeSv, int toeSv, boolean lft) {
    legSvo = legSv;
    kneeSvo = kneeSv;
    toeSvo = toeSv;
    left = lft;
    svoController = ctrler;
    kneeBaseAngle = 90;
    legBaseAngle = 90;
    toeBaseAngle = 90;
  }
  
void RobotFoot::setBasePos(int legBaseAngle, int kneeBaseAngle, int toeBaseAngle) {
    this->legBaseAngle = legBaseAngle;
    this->kneeBaseAngle = kneeBaseAngle;
    this->toeBaseAngle = toeBaseAngle;
  }
  
  void RobotFoot::kneePos(int kneeAngle) {
    if(!left) {
      kneeAngle = -kneeAngle;
    }

    svoController->set(kneeSvo, kneeBaseAngle + kneeAngle);
  }
  
  void RobotFoot::toePos(int toeAngle) {
    if(!left) {
      toeAngle = -toeAngle;
    }

    svoController->set(toeSvo, toeBaseAngle + toeAngle);
  }
    
  void RobotFoot::legPos(int legAngle) {
    if(left) {
      legAngle = -legAngle;
    }

    svoController->set(legSvo, legBaseAngle + legAngle);
  }
  
  
  void RobotFoot::liftUp() {
    kneePos(45);
    toePos(80);
  }
  
  void RobotFoot::putDown() {
    kneePos(-45);
    toePos(35);
  }
  
  void RobotFoot::forward() {
    legPos(35);
  }
  
  void RobotFoot::back() {
    legPos(-35);
  }
  
  void RobotFoot::toeBasePos() {
    svoController->set(toeSvo, toeBaseAngle);
  }
  
  void RobotFoot::kneeBasePos() {
    svoController->set(kneeSvo, kneeBaseAngle);
  }
  
  void RobotFoot::legBasePos() {
    svoController->set(legSvo, legBaseAngle);
  }
