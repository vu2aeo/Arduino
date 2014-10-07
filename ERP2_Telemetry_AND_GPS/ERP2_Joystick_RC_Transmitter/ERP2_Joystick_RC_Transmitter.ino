#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

//Read inputs from an analog joystick
//convert to speed values for a BO MotorPair
//transmit these over RF24 radio link
//to a remote recevier


//NRF24 Transmitter on Arduino Uno
//
int cePin = 9;
int csPin = 10;

//NRF24 Transmitter on Arduino Mega
//
//int cePin = 40;
//int csPin = 53;

int joy_turnPin = A4;
int joy_spdPin = A5;


int txData[2];//create data packet

//init zero errors in both joystick axes

float turnErr = 0;
float spdErr = 0;
 
RF24 radio(cePin,csPin);
 
const uint64_t pipe = 0xE8E8F0F0E1LL;
 
void setup(void)
{
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
  
  //To calibrate: read 100 values from joystick
 
  int calibIterations = 3000;  
  
  for (int i=0; i <= calibIterations; i++)
  {
    turnErr +=512 - analogRead(joy_turnPin);
    spdErr +=512 - analogRead(joy_spdPin);
  }
  
  // find calibration error;
  
  turnErr /= calibIterations;
  spdErr /= calibIterations;
  
//  Serial.print("Joystick Zero Error Readings:");
//  Serial.print("Spd:");
//  Serial.print(spdErr);
//  Serial.print(",");
//  Serial.print("Turn:");
//  Serial.println(turnErr);
 
}

float removeError(float val, float err)
{
  if (err > 0) 
  {
    return (val-err);
  
  } else return (val+err);
   
}

void CreateMotorCommands(float spd, float turn, int* mCmd)
{

       if(turn < -50.0) //turn left
        {
          mCmd[0] = -spd;
          mCmd[1] = spd;
        } else if(turn > 25.0) //turn right
        {
          mCmd[0] = spd;
          mCmd[1] = -spd;
        }  else //go straight 
        {
          mCmd[0] = spd;
          mCmd[1] = spd;
        }
  //Since the BOMotor class only allows motor commands between
  //-255 and 255, constrain both commands within this limit
  
  
     mCmd[0] = map(mCmd[0],-511,511,-255,255);
     mCmd[1] = map(mCmd[1],-511,511,-255,255);
  
}
 
void loop()
{

  //read commands from the joystick
  float turn = analogRead(joy_turnPin) - 511;
  float spd = analogRead(joy_spdPin) - 511;
  
  //remove calibaration errors
  
  turn = removeError(turn,turnErr);
  spd = removeError(spd,spdErr);

//Order the motors to turn only if the speed ordered is greater
//than about 25 units of joystick movement

  if(abs(spd) >= 25)
  {

    CreateMotorCommands(spd, turn, txData);
  
  }else
  {
    //if the spd level is < 25, set both motors to zero speed
    
    txData[0] = 0;
    txData[1] = 0;
    
  }
  
  //debug the motor commands
  Serial.print("\t LEFT Motor:");
  Serial.print(txData[0]);
  Serial.print("\t ,RIGHT Motor:");
  Serial.println(txData[1]);  
        
//transmit over the radio link
  radio.write(txData, sizeof(txData));
  
  delay(500);//repeat every 20 milliseconds

}


