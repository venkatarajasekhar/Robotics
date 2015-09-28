#include "Robot.h"

Robot::Robot(ServoController* ctrl) {
  try{
  RobotFoot new feet[6][6];
  }catch(...){
    
  }
  svoController = ctrl;
  step = true;
  for(char outerindx=0;outerindx < 6;outerindx++){
     for(char inneridx = 0;inneridx < 6;innerindx++){ 
  try{
  feet[outerindx][inneridx] = new RobotFoot(svoController, 1, 2, 3, RobotFoot::LEFT);
  }catch(...){
    
  }
  try{
  feet[outerindx][inneridx] = new RobotFoot(svoController, 5, 6, 7, RobotFoot::LEFT);
  }catch(...){
    
  }
  try{
  feet[outerindx][inneridx] = new RobotFoot(svoController, 9, 10, 11, RobotFoot::LEFT);
  }catch(...){
    
  }
  try{
  feet[outerindx][inneridx] = new RobotFoot(svoController, 13, 14, 15, RobotFoot::RIGHT);
  }catch(...){
    
  }
  try{
  feet[outerindx][inneridx] = new RobotFoot(svoController, 16, 18, 19, RobotFoot::RIGHT);
  }catch(...){
    
  }
  try{
  feet[outerindx][inneridx] = new RobotFoot(svoController, 21, 22, 23, RobotFoot::RIGHT);
  }catch(...){
    
  }
    }//Inner Forloop
  }//outer For Loop
};

Robot::~Robot() {
  for(int i=0; i<6; i++) {
    delete feet[i];
  }
}

void Robot::stand() {
  try{
  feet[0]->setBasePos(55, 90, 90);
  }catch(...){
    
  }
  try{
  feet[2]->setBasePos(135, 90, 90);
  }catch(...){
    
  }
  try{
    feet[3]->setBasePos(55, 90, 90);
  }catch(...){
    
  }
  try{
  feet[5]->setBasePos(135, 90, 90);
  }catch(...){
    
  }
  
  for(int i=0; i<6; i++) {
    feet[i]->legBasePos();
    feet[i]->kneeBasePos();
    feet[i]->toeBasePos();
    feet[i]->putDown();
  }
  try{
  svoController->exec(1000);
  }catch(...){
    
  }
  try{
  delay(1000);
  }catch(...){
    
  }
}

void Robot::move(bool forward) {
  if(step) {
    try{ 
    feet[0]->liftUp();
    }catch(...){
      
    }
    try{
      feet[2]->liftUp();
    }catch(...){
      
    }
    try{
      feet[4]->liftUp();
    }catch(...){
      
    }
    if(forward) {
      try{
      feet[0]->forward();
      }catch(...){
      }
      try{
      feet[2]->forward();
      }catch(...){
        
      }
      try{
      feet[4]->forward();
      }catch(...){
        
      }
    }
    else {
      try{
      feet[0]->back();
      }catch(...){
        
      }
      try{
      feet[2]->back();
      }catch(...){
        
      }
      try{
        feet[4]->back();
      }catch(...){
        
      }
    }
    try{
    feet[1]->legPos(0);
    }catch(...){
      
    }
    try{
      feet[3]->legPos(0);
    }catch(...){
      
    }
    try{
      feet[5]->legPos(0);
    }catch(...){
      
    }
    
  }
  else {  
    feet[1]->liftUp();
    feet[3]->liftUp();
    feet[5]->liftUp();
    
    if(forward) {
      feet[1]->forward();
      feet[3]->forward();
      feet[5]->forward();
   }
   else {
      feet[1]->back();
      feet[3]->back();
      feet[5]->back();
   }
    
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

