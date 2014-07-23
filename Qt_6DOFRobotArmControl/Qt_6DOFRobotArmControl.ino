#include <Servo.h>
#define NO_OF_FIELDS 6

Servo base, shoulder, foreArm, wristFlex, wristRotate, claw;

int inCommand[NO_OF_FIELDS];
int ledPin = 13;

void EchoData(int echoWord[])
{
   Serial.print("*");
    
    float total;
    
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
  
  base.attach(3);
  shoulder.attach(5);
  foreArm.attach(6);
  wristFlex.attach(9);
  wristRotate.attach(10);
  claw.attach(11);
  
  //initialise all arms
  
  base.write(90);
  shoulder.write(150);
  foreArm.write(40);
  wristFlex.write(90);
  wristRotate.write(90);
  claw.write(175);
  
  pinMode(ledPin, OUTPUT);
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
      digitalWrite(ledPin, HIGH);
    }
    
    digitalWrite(ledPin,LOW);
    
    //echo the incoming command sequence
    
    EchoData(inCommand);
    
    //now do something with the inCommand[] array....
    
    base.write(inCommand[0]);
    
    shoulder.write(inCommand[1]);
    
    foreArm.write(inCommand[2]);
    
    wristFlex.write(180 - inCommand[3]);
    
    wristRotate.write(inCommand[4]);
    
    claw.write(inCommand[5]);
    
    //clear the inCommand[] array
    
    ClearOldData(inCommand);
  
    
  }
  

}


