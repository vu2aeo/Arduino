#include <Servo.h>

#define NO_OF_FIELDS 1

Servo joint[6];

int inCommand[NO_OF_FIELDS];

void EchoData(int echoWord[])
{
   Serial.print("*");
    
    float total = 0;
    
    for (int i = 0; i < NO_OF_FIELDS; i++)
    {
      Serial.print((int)echoWord[i]);
      
      total+= inCommand[i];
      
      Serial.print(",");
    }
    Serial.print((int)total);
    Serial.print(",");
    Serial.print("*");
    Serial.print("&");
}

void ClearOldData(int oldData[])
{
  for (int i = 0; i < NO_OF_FIELDS; i++)
  {
    oldData[i] = 0;
  }
}



void setup()
{
  Serial. begin(38400);
  
  joint[0].attach(8);
  joint[1].attach(9);
  joint[2].attach(10);
  joint[3].attach(11);
  joint[4].attach(12);
  joint[5].attach(13);
  
  
//  //initialise all arms

  joint[0].write(90);
  joint[1].write(140);
  joint[2].write(20);
  joint[3].write(20);
  joint[4].write(110);
  joint[5].write(150);

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
    
    EchoData(inCommand);
    
    //now do something with the inCommand[] array....

    //ObeyCommand(inCommand);
    
    ClearOldData(inCommand);
     
    
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



