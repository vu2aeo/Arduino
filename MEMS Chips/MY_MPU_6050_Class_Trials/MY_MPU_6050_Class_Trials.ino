#include "my_mpu_6050.h"
#include "qttalker.h"
#include <Wire.h>

MY_MPU_6050 mpu1;

QtTalker line1(9600);

float gyroData[3];

float accelData[3];

float outPkt[2];

void setup()
{
  mpu1.Initialise();
  
  line1.Connect();
}

void loop()
{
  mpu1.Update();
  
  gyroData[0] = mpu1.GetGyroReading(0);
  gyroData[1] = mpu1.GetGyroReading(1);
  gyroData[2] = mpu1.GetGyroReading(2);
  
  accelData[0] = mpu1.GetAccelerometerReading(0);
  accelData[1] = mpu1.GetAccelerometerReading(1);
  accelData[2] = mpu1.GetAccelerometerReading(2);
  
//  line1.SendDataPacketToQt(gyroData);

//  line1.SendDataPacketToQt(accelData);

outPkt[0] = gyroData[0];
outPkt[1] = accelData[1];

//for (int i =0; i < 3; i++)
//{
//  outPkt[i] = gyroData[i];
//  outPkt[i+3] = accelData[i];
//}

line1.SendDataPacketToQt(outPkt);
 
  delay(50);
}
