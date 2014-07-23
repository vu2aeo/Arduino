#include "mpu6050.h"
#include "bomotorpair.h"
#include "Wire.h"

BOMotorPair bot1(5,6,3,8,9,10);
MPU6050 sensor1;
float filteredOutput;
float oldPos = 0;
float kD = 0;
float kP = 1;

unsigned long t0 = micros();
unsigned long t1 = 0;
int dT;

float FilterSensorData(float gyro, float accel)
{
  
  dT = t1 - t0;
  
  filteredOutput = 0 * (filteredOutput + gyro * dT/1000000) + 1 * accel;
  
  t0 = t1;
  
  return filteredOutput;
}


void setup()
{
  bot1.SetMoveDirection(forward);
  bot1.SetMoveSpeed(0);
  
  Serial.begin(115200);
  
  sensor1.Initialise();
}

void loop()
{
  sensor1.Update();
  
  t1 = micros();
  
  float g = sensor1.GetGyroReading(1);
  
  float a = sensor1.GetAccelerometerReading(0);
  
  float f_val = FilterSensorData(g,a);
  
  float dAngle = (f_val - oldPos);
  
  float moImpulse = kD * dAngle + kP * abs(f_val);
  
  if (f_val < 0)
 {
   bot1.SetMoveDirection(backward);
 } else
 {
   bot1.SetMoveDirection(forward);
 }
 
 int botSpeed = map((int)abs(moImpulse), 0,70, 30,255);
 
 bot1.SetMoveSpeed(botSpeed);
 
 bot1.Move();
 
// Serial.print("dT:");
// Serial.print(dT);
// Serial.print("     Angle:");
// Serial.print(f_val);
// Serial.print("     Motor Impulse:");
// Serial.println(botSpeed);
// 
 
 delayMicroseconds(10000);  
  
}
