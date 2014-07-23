#include <Servo.h>

Servo j1[6];

void setup()
{
  j1[0].attach(8);
  j1[1].attach(9);
  j1[2].attach(10);
  j1[3].attach(11);
  j1[4].attach(12);
  j1[5].attach(13);
  
  j1[0].write(90);
  j1[1].write(140);
  j1[2].write(20);
  j1[3].write(20);
  j1[4].write(110);
  j1[5].write(150);
  
  
  Serial.begin(9600);
}

void loop()
{
  if(Serial.available())
  {
     
    int goAngle = Serial.parseInt();
    
    while (Serial.read() != -1)
    {
      //loops here until serial buffer becomes empty
      //Serial.println(millis() - time1);
      
    }
    
    j1[0].write(goAngle);
    
    Serial.println(goAngle);
  }
  
}
