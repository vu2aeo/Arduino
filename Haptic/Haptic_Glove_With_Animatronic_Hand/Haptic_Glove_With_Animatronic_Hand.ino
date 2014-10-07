#include "robotfinger.h"
#include "robotthumb.h"
#include <Servo.h>
 
#define SMOOTH_CONST 20 // smoothing loop size
 
//output pin allocation on UNO
//thumb rotator pin 3
//thumb flexor pin 5
//index pin 6
//middle pin 9
//ring pin 10
//little pin 11
 
RobotFinger finger[4];
 
RobotThumb thumb;
 
//sensor pins and sensor limits
 
int sensorPin[6] = {0,1,2,3,4,5};//all sensors on analog pins
 
int sensorMaxVal[6] = {0,0,0,0,0,0};
 
int sensorMinVal[6] = {0,0,0,0,0,0};
 
int finalAngle[6] = {0,0,0,0,0,0};
 
int totalAngle[6] = {0,0,0,0,0,0};//used for smoothing purposes to reduce jerkiness
 
//finger variables
 
int fingerPin[4] = {6,9,10,11};
 
int maxFlexAngle[4] = {140,180,180,180};
 
int minFlexAngle[4] = {0,20,20,50};
 
bool flexesAtMax[4] = {true,false,false,false};//is the finger flexed when servo is at maxFlexAngle?
 
int t0;
 
void setup()
{
 
  Serial.begin(9600);
 
  t0 = millis();
   
  //set up the thumb
   
  thumb.SetRotationParameters(3,130,40);
 
  thumb.SetFlexorParameters(5,120,20);
   
  thumb.SetFlexAndOppositionFlags(true, false);//when thumb is fully flexed or fully opposed, are the servos at their maximum angle?
   
  //set up the fingers
   
  for (int i = 0; i < 4; i++)
  {
    finger[i].SetParameters(fingerPin[i],maxFlexAngle[i],minFlexAngle[i]);
     
    finger[i].SetFlexesAtMaxPosFlag(flexesAtMax[i]);
  }
}
 
void loop()
{
  //relax everything
   
  thumb.Relax();
   
  for (int i = 0; i < 4; i++)
  {
    finger[i].Relax();
  }
  // run calibration for 20 seconds
   
  Serial.println("Calibrating.......");
   
  for (int i = 0; i < 6; i++)
  {
    sensorMinVal[i] = analogRead(sensorPin[i]);
  }
 
  while (millis() - t0 < 20000) // calibrate for 20 seconds
  {
    for (int i = 0; i < 6; i++)
      {
        int sensorRawVal = analogRead(sensorPin[i]);
 
        if (sensorRawVal >= sensorMaxVal[i])
          {
            sensorMaxVal[i] = sensorRawVal;
          }
        else if (sensorRawVal <= sensorMinVal[i])
          {
            sensorMinVal[i] = sensorRawVal;
          }
      }
 
  }
 
  //    Read Continuously
 
  while(true)
  {
    //run a large smoothing loop of ten iterations
     
        for (int h = 0; h < SMOOTH_CONST; h++)
        {
       
          for (int i = 0; i < 6; i++)
          {
            //read each of the analog pins
     
            int readVal = analogRead(sensorPin[i]);
             
            //proportionalise the raw reading to within max and min
             
            constrain(readVal, sensorMinVal[i], sensorMaxVal[i]);
             
            //calculate the final GOTO angle for each actuator
             
            finalAngle[i] = abs(1.1*(readVal - sensorMinVal[i]) * 100/ (sensorMaxVal[i] - sensorMinVal[i]));
             
            //make sure the final angle is ok in terms of sign and value
     
            if (finalAngle[i] < 0) finalAngle[i]*=-1;
             
            if (finalAngle[i] > 100) finalAngle[i] = 100;
             
            if (finalAngle[i] < 20) finalAngle[i] = 0;
             
            totalAngle[i]+=finalAngle[i];
     
          }
        }
     
      //move the fingers
     
      thumb.RotateAndFlex(totalAngle[0]/SMOOTH_CONST, totalAngle[1]/SMOOTH_CONST);
      //
      //     Serial.print("T Rot:");
      //     Serial.print(finalAngle[0]);
      //     Serial.print(",T Flex:");
      //     Serial.print(finalAngle[1]);
     
    for (int i = 0 ; i < 4; i++)
    {
      //finger[i].Flex(finalAngle[i]);
      //       Serial.print("F(");
      //       Serial.print(i);
      //       Serial.print(") Flex:");
      //       Serial.print(finalAngle[i]);
      finger[i].Flex(totalAngle[i+2]/SMOOTH_CONST);
    }
   
    for (int f = 0; f < 6; f++)
    {
      totalAngle[f] = 0;
    }
   
    //Serial.println();
   
  }
 
}
