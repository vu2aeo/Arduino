#include <Servo.h>
#include <SoftwareSerial.h>

#define NO_OF_FIELDS 8

Servo joint[6];

int inCommand[NO_OF_FIELDS];

SoftwareSerial ERPSerial(8,7);

void EchoData()
{
   Serial.print("*");
    
    float total;
    
    for (int i = 0; i < NO_OF_FIELDS; i++)
    {
      Serial.print((int)inCommand[i]);
      
      total+= inCommand[i];
      
      Serial.print(",");
    }
    Serial.print((int)total);
    Serial.print(",");
    Serial.print("*");
    Serial.print("&");
}

void ClearOldData()
{
  for (int i = 0; i < NO_OF_FIELDS; i++)
  {
    inCommand[i] = 0;
  }
}

void SendData()
{
  int checkSum = 0;//create a checksum
  
  ERPSerial.print("***");//send data wrapper
  
  for (int i=0;i<NO_OF_FIELDS;i++)
  {
    checkSum+=inCommand[i];
    ERPSerial.print(inCommand[i]);
    ERPSerial.print(",");
  }
  
  //send checksum
  ERPSerial.print(checkSum);
  ERPSerial.print("&&&");//send end wrapper
}



void setup()
{
  Serial. begin(38400);
  ERPSerial.begin(38400);
  
}

void loop()
{
  if(Serial.available())
  {
    for(int i = 0; i < NO_OF_FIELDS; i++)
    {
      inCommand[i] = Serial.parseFloat();
    }
    
    unsigned long time1 = millis();
    
    while (Serial.read() != -1)
    {
      //loops here until serial buffer becomes empty
      //Serial.println(millis() - time1);
      
    }
    
    //echo the incoming command sequence
    
    EchoData();
    
    //now do something with the inCommand[] array....

    SendData();
    
    ClearOldData();
     
    
  }
  

}

void ObeyCommand(int goAngle[])
{
  //the first two fields are motor commands
  
  //fields 2 to 7 are robotic arm commands
  
  joint[0].write(goAngle[2]);
  joint[1].write(goAngle[3]);
  joint[2].write(goAngle[4]);
  joint[3].write(goAngle[5]);
  joint[4].write(goAngle[6]);
  joint[5].write(goAngle[7]);
}



