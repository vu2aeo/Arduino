#include "bomotorpair.h"

BOMotorPair bot1(4,5,3,7,8,9);

void setup()
{
    bot1.SetMoveSpeed(255);
}

void loop()
{
  bot1.SetMoveDirection(forward);
  
  bot1.Move();
  
  delay(2000);
  
  bot1.SetMoveDirection(backward);
  
  delay(2000);
    
}
