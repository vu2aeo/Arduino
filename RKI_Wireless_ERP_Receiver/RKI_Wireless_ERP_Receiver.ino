//To receive wireless data and control and ERP

#include "bomotorpair.h"

BOMotorPair ERP(32,33,6,34,35,7);

#define NO_OF_FIELDS 3

float inCommand[NO_OF_FIELDS];

void ClearOldData(float oldData[])
{
  for (int i = 0; i < NO_OF_FIELDS; i++)
  {
    oldData[i] = 0;
  }
}

void ObeyCommand(float inCommand[])
{
    //echo the data to Serial0
    
    for(int i = 0; i < NO_OF_FIELDS - 1; i++)
    {
      Serial.print(inCommand[i]);
      Serial.print(",   ");
    }
//    Serial.print("Incoming size:");
//    Serial.print(sizeof(inCommand));
    Serial.println();
    
    ERP.MoveWheelsIndependently(inCommand[0],inCommand[1]);
}

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(38400);

  // set the data rate for the SoftwareSerial port
  Serial1.begin(38400);
}

void loop() // run over and over
{
  float checkSum = 0;
  
  if (Serial1.available())
  {
    for(int i = 0; i < NO_OF_FIELDS; i++)
    {
      inCommand[i] = Serial1.parseFloat();
         
      checkSum +=inCommand[i];
    }
    
    while (Serial1.read() != -1)
    {
      //loops here until serial buffer becomes empty
    }
    
    //In case the checkSum is OK,
    //Do something with the incoming command.....
    
    if (checkSum - inCommand[NO_OF_FIELDS-1] == inCommand[NO_OF_FIELDS-1])
    {
      ObeyCommand(inCommand);
      
    } else
    {
      //Serial.println("Error in Data...");
      
      ObeyCommand(inCommand);
      
      while (Serial1.read() != '&')
      {
          //loops here until serial buffer becomes empty
      }
      ClearOldData(inCommand);
    }
   
   ClearOldData(inCommand);
    
  }
  
}
