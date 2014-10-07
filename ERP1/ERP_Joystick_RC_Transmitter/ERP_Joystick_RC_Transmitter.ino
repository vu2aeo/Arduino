#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

//Read values from an analog joystick
//convert to speed values for a BO MotorPair
//transmit these over RF24 radio link
//to a remote controlled robot


//NRF24 Transmitter on Arduino Uno

//int cePin = 9;
//int csPin = 10;

//NRF24 Transmitter on Arduino Mega
//
int cePin = 40;
int csPin = 53;

int joy_offsetPin = 4;
int joy_spdPin = 5;

float motorSpd[2];

int txData[2];//create data packet

float offsetErr = 0;
float spdErr = 0;
 
RF24 radio(cePin,csPin);
 
const uint64_t pipe = 0xE8E8F0F0E1LL;
 
void setup(void)
{
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
  
  //To calibrate: read 100 values from joystick 
  
  for (int i=0;i<=250;i++)
  {
    offsetErr +=512 - analogRead(joy_offsetPin);
    spdErr +=512 - analogRead(joy_spdPin);
  }
  
  // find calibration error;
  
  offsetErr /= 250;
  spdErr /= 250;
  
  Serial.print(offsetErr);
  Serial.print(",");
  Serial.println(spdErr);
  
}

float removeError(float val, float err)
{
  if (err>0) val-=err;
  if (err<0) val+=err;
  return val; 
}
 
void loop(void)
{
  //read commands from the joystick
  float offset = analogRead(joy_offsetPin);
  float spd = analogRead(joy_spdPin);
  
  //remove calibaration errors
  
  offset = removeError(offset,offsetErr);
  spd = removeError(spd,spdErr);

  //convert spd to between -1 to +1
  
  spd = (spd - 512)/512;
  
//  Serial.print("Spd:");
//  Serial.print(spd);
//  Serial.print("    Offset:");
//  Serial.println(offset);
  
  if (offset>=512+20)//if joystick is to the right
  {
    motorSpd[1] = (offset)/512 * spd * 100;//reduce left motor speed
    
    if (offset>=900)//if joystick is at extremity
    {
      motorSpd[1] *=-2;//reverse left motor
    }
       
    motorSpd[0] = 512 * spd;//right motor normal
    
  } 
  
  else if (offset<=512 - 20) //if joystick is to the left
  
  {
    motorSpd[0] = (512 + offset)/512 * spd * 100;//reduce right motor speed
    
    if (offset<=100)//if joystick is at extremity
    {
      motorSpd[0] *=-2;//reverse right motor
    }
    
    motorSpd[1] = 512 * spd;//left motor normal
    
  } 
  else //keep both motors at full power
  
  {
    motorSpd[0] = 512 * spd;
    
    motorSpd[1] = 512 * spd;
  }
  
  //constrain motor speeds from -512 to +512
    
  constrain(motorSpd[0],-512,512);
  constrain(motorSpd[1],-512,512);
    
  //write to serial monitor for debugging
  
  Serial.print("Left Motor:");
  Serial.print((int)motorSpd[0]);
  Serial.print("    Right Motor:");
  Serial.println((int)motorSpd[1]);
  
  txData[0] = (int)motorSpd[0];
  txData[1] = (int)motorSpd[1];
        
  //transmit over the radio link
  radio.write(txData, sizeof(txData));
  
  //delay(10);//repeat every 20 milliseconds
 
}


