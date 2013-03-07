
#include "Motor.h"


void setup() {
  
}

void loop() {
  Motor m1(2, 3), m2(4, 5);
  m1.back(200);
  m2.back(200);
    
    
  delay(1000);
    
// m.brake();
 delay(200);
 m1.forward(200);
 m2.forward(200);
    
 delay(1000);
  
}
