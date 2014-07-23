#include "robotthumb.h"
#include <Servo.h>

RobotThumb thumb1;

void setup()
{
  thumb1.SetRotationParameters(9,130,40);
  thumb1.SetFlexorParameters(3,120,20);
}

void loop()
{
  
}




