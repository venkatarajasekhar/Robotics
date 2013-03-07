#ifndef MOTOR_H
#define MOTOR_H

class Motor {
protected:
  int pin1, pin2;
  
public:
  Motor(int pin1, int pin2);
  
  void forward(int speed);
  
  void back(int speed);
  
  void brake();
};

#endif
