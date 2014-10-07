//To receive wireless data and control an ERP
#include <Servo.h>
#include "bomotorpair.h"

BOMotorPair ERP(32,33,6,34,35,7);

Servo joint[6];

#define NO_OF_FIELDS 9

float inCommand[NO_OF_FIELDS];

void ClearOldData()
{
  for (int i = 0; i < NO_OF_FIELDS; i++)
  {
    inCommand[i] = 0;
  }
}

void ObeyCommand()
{
    //echo the data to Serial0
    
//    for(int i = 0; i < NO_OF_FIELDS - 1; i++)
//    {
//      Serial.print(inCommand[i]);
//      Serial.print(",   ");
//    }
//////    Serial.print("Incoming size:");
//////    Serial.print(sizeof(inCommand));
//    Serial.println();
    
    //turn motors
    
    ERP.MoveWheelsIndependently(inCommand[0],inCommand[1]);
    
    //follow robotic arm servo orders
    
    joint[0].write(inCommand[2]);
    joint[1].write(inCommand[3]);
    joint[2].write(inCommand[4]);
    joint[3].write(inCommand[5]);
    joint[4].write(inCommand[6]);
    joint[5].write(inCommand[7]);
//    
    
}

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(38400);

  // set the data rate for the SoftwareSerial port
  Serial1.begin(38400);
  
  //Attach servos
  
  joint[0].attach(8);
  joint[1].attach(9);
  joint[2].attach(10);
  joint[3].attach(11);
  joint[4].attach(12);
  joint[5].attach(13);
  
  
//  //initialise all arms

  joint[0].write(105);
  joint[1].write(180);
  joint[2].write(0);
  joint[3].write(0);
  joint[4].write(95);
  joint[5].write(150);
}

void loop() // run over and over
{
  float checkSum = 0;
  
  if (Serial1.available())
  {
    Serial.print("REceiving..");
    
    for(int i = 0; i < NO_OF_FIELDS - 1; i++)
    {
      inCommand[i] = Serial1.parseFloat();
      
      Serial.print(inCommand[i]);
      Serial.print(",");
         
      checkSum +=inCommand[i];
    }
       
    float totalIn = Serial1.parseFloat();
    
    Serial.print("...=");
    Serial.print(totalIn);
    Serial.print("...");
    
    while (Serial1.read() != -1)
    {
      //loops here until serial buffer becomes empty
    }
    
    //In case the checkSum is OK,
    //Do something with the incoming command.....
    
    if (checkSum - totalIn == 0)
    {
      Serial.println("Data OK...");
      
      ObeyCommand();
      
    } else
    {
      Serial.println("Error...");
      
      //ObeyCommand();
      
      while (Serial1.read()!='*')
      {
          //loops here until serial buffer becomes empty
          
      }
      ClearOldData();
    }
   
   ClearOldData();
    
  }
  
}
