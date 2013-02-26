#include "Robot.h"

Robot::Robot(ServoController* ctrl) {
  svoController = ctrl;
  step = true;
  feet[0] = new RobotFoot(svoController, 1, 2, 3, RobotFoot::LEFT);
  feet[1] = new RobotFoot(svoController, 5, 6, 7, RobotFoot::LEFT);
  feet[2] = new RobotFoot(svoController, 9, 10, 11, RobotFoot::LEFT);
  feet[3] = new RobotFoot(svoController, 13, 14, 15, RobotFoot::RIGHT);
  feet[4] = new RobotFoot(svoController, 16, 18, 19, RobotFoot::RIGHT);
  feet[5] = new RobotFoot(svoController, 21, 22, 23, RobotFoot::RIGHT);
};

Robot::~Robot() {
  for(int i=0; i<6; i++) {
    delete feet[i];
  }
}

void Robot::init() {
  feet[0]->setBasePos(55, 90, 90);
  feet[2]->setBasePos(135, 90, 90);
  feet[3]->setBasePos(55, 90, 90);
  feet[5]->setBasePos(135, 90, 90);
  
  for(int i=0; i<6; i++) {
    feet[i]->legBasePos();
    feet[i]->kneeBasePos();
    feet[i]->toeBasePos();
    feet[i]->putDown();
  }
  
  svoController->exec(1000);
  delay(1000);
}


void Robot::forward() {
  if(step) {
  
    feet[0]->liftUp();
    feet[2]->liftUp();
    feet[4]->liftUp();
    
    feet[0]->forward();
    feet[2]->forward();
    feet[4]->forward();
    
    feet[1]->legPos(0);
    feet[3]->legPos(0);
    feet[5]->legPos(0);
    
  }
  else {  
    feet[1]->liftUp();
    feet[3]->liftUp();
    feet[5]->liftUp();
    
    feet[1]->forward();
    feet[3]->forward();
    feet[5]->forward();
    
    feet[0]->legPos(0);
    feet[2]->legPos(0);
    feet[4]->legPos(0);
  }
  
  step = !step;
  
  svoController->exec(400);
  delay(400);
    
  for(int i=0; i<6; i++) {
    feet[i]->putDown();
  }
  svoController->exec(400);
  delay(400);
}

