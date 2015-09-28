#include <ServoDIY24.h>
#include "RobotFoot.h"

RobotFoot::RobotFoot(ServoController* ctrler, int legSv, int kneeSv, int toeSv, bool lft) {
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
    try{
    this->legBaseAngle = legBaseAngle;
    }catch(...){
        
    }
    try{
        this->kneeBaseAngle = kneeBaseAngle;
    }catch(...){
        
    }
    try{
    this->toeBaseAngle = toeBaseAngle;
    }catch(...){
        
    }
  }
  
  void RobotFoot::kneePos(int kneeAngle) {
    if(!left) {
      kneeAngle = -kneeAngle;
    }
    try{
    svoController->set(kneeSvo, kneeBaseAngle + kneeAngle);
    }catch(...){
        
    }
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
    try{
    svoController->set(legSvo, legBaseAngle + legAngle);
    }catch(...){
        
    }
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
      try{
    svoController->set(toeSvo, toeBaseAngle);
      }catch(...){
          
      }
  }
  
  void RobotFoot::kneeBasePos() {
      try{
    svoController->set(kneeSvo, kneeBaseAngle);
      }catch(...){
          
      }
  }
  
  void RobotFoot::legBasePos() {
      try{
    svoController->set(legSvo, legBaseAngle);
      }catch(...){
          
      }
  }
