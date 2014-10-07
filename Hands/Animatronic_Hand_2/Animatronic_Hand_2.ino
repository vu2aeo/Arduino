#include "robotfinger.h"

#include <Servo.h>

//pin designations...
//thumb rotator 3
//thumb flexor 5
//index 6
//middle 9
//ring 10
//little 11

RobotFinger finger[4];

RobotFinger thumb;

int fingerPin[4] = {6,9,10,11};

int maxFlexAngle[4] = {140,180,180,180};

int minFlexAngle[4] = {0,20,20,50};

bool flexesAtMax[4] = {true,false,false,false};

void setup()
{
  //set up the thumb
  
  thumb.SetParameters(5,120,40);

  thumb.SetFlexesAtMaxPosFlag(true);
  
  //set up the other fingers
  
  for (int i = 0; i < 4; i++)
  {
    finger[i].SetParameters(fingerPin[i],maxFlexAngle[i],minFlexAngle[i]);
    
    finger[i].SetFlexesAtMaxPosFlag(flexesAtMax[i]);
  }
}

void loop()
{
  DoFlexDemo();
  
   
}

void DoFlexDemo()
{
    //relax all the fingers together
  
  thumb.Relax();
  
  delay(200);
  
  for (int i = 0; i < 4; i++)
  {
    finger[i].Relax();
  }
  
  delay(1000);
  
  //flex all the fingers one by one
  
  for (int i = 0; i < 4; i++)
  {
    finger[i].FlexMax();
    delay(500);
  }
  
  thumb.FlexMax();
  
  //relax all the fingers one by one
    
  thumb.Relax();
  
  for (int i = 4; i > 0; i--)
  {
    finger[i-1].Relax();
    delay(500);
  }
  
  //flex all fingers at once
  
  for (int i = 0; i < 5; i++)
  {
    finger[i].FlexMax();
  }
  
  delay(200);
  
  thumb.FlexMax();
  
  delay(1000);
}
