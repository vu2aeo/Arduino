#include <SoftwareSerial.h>

#define NO_OF_FIELDS 2

SoftwareSerial mySerial(8,7); // RX, TX

int joy_offsetPin = 4;
int joy_spdPin = 5;

int offsetErr = 0;
int spdErr = 0;

float txData[NO_OF_FIELDS];

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(38400);

  // set the data rate for the SoftwareSerial port
  mySerial.begin(38400);
  
    //To calibrate: read 100 values from joystick 
  
  for (int i=0;i<=250;i++)
  {
    offsetErr +=512 - analogRead(joy_offsetPin);
    spdErr +=512 - analogRead(joy_spdPin);
  }
  
    // find calibration error;
  
  offsetErr /= 250;
  spdErr /= 250;
  
}

float removeError(float val, float err)
{
  if (err>0) val-=err;
  if (err<0) val+=err;
  return val; 
}

void SendData(float txData[])
{
  int checkSum;//create a checksum
  
  mySerial.print("***");//send data wrapper
  
  for (int i=0;i<NO_OF_FIELDS;i++)
  {
    checkSum+=txData[i];
    mySerial.print(txData[i]);
    mySerial.print(",");
  }
  
  //send checksum
  mySerial.print(checkSum);
  mySerial.print("&&&");//sebdend wrapper
}

void ParseAndSendMotorCommands(float offset, float spd)
{
  
  float lval,rval;
  //convert spd to between -1 to +1
  
  spd = (spd - 512)/512;
  
//  Serial.print("offset:");
//  Serial.print(offset);
//  Serial.print("    spd:");
//  Serial.println(spd);
  
 
  if (offset>=512+20)//if joystick is to the right
  {
      
    rval = 512 * spd;//right motor normal
    
    //reverse the left motor
    
    lval = (offset - 512) * spd * -1;
    
  } 
  
  else if (offset<=512 - 20) //if joystick is to the left
  
  {
    
    lval = 512 * spd;//left motor normal
    
    //reverse the right motor
    
    rval = (512 - offset) * spd * -1;
    
  } 
  else //keep both motors at full power
  
  {
    lval = 512 * spd;
    
    rval = 512 * spd;
  }
  
  //constrain motor speeds from -512 to +512
    
  constrain(lval,-512,512);
  constrain(rval,-512,512);
  
  txData[0] = lval/2;
  txData[1] = rval/2;
  
//  Serial.print("left:");
//  Serial.print(lval);
//  Serial.print("    right:");
//  Serial.println(rval);
    
  //write to serial treansmitter
  
  SendData(txData);
  
}

void loop() // run over and over
{
 //read commands from the joystick
  float offset = analogRead(joy_offsetPin);
  float spd = analogRead(joy_spdPin);
  
  //remove calibaration errors
  
  offset = removeError(offset,offsetErr);
  spd = removeError(spd,spdErr);
  
  ParseAndSendMotorCommands(offset, spd);
  
  delay(50);
 
}
