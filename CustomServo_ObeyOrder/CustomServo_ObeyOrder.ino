#include "dcmotor.h"

DCMotor motor1(42,43,2);

int potPin = 4;

double orderAngle;

void setup()
{
  Serial.begin(115200);
  
  pinMode(42,OUTPUT);
  
  pinMode(43,OUTPUT);
  
  motor1.SetTurnSpeed(255);
  
}

void loop()
{
   if (Serial.available())
  {
    orderAngle = Serial.parseFloat();
    
    Serial.print("Order Recieved:");
    
    Serial.println(orderAngle);
    
    ObeyServoOrder(orderAngle);
  }
  
  PrintServoPosition(orderAngle);
  
}

void ObeyServoOrder(double orderAngle)
{
  double potRest = (double)analogRead(potPin)/1023 * 47;
  
  double currAngle = map(potRest,0.64,38,0,180);
  
  //make sure the ordered angle is within limits
  
  orderAngle = constrain(orderAngle,0,180);
  
  while (abs(orderAngle - currAngle) > 5) //there is a posn error
  {
    potRest = (double)analogRead(potPin)/1023 * 47;
  
    currAngle = map(potRest,0.64,38,0,180);
  
    if (orderAngle > currAngle)
    {
      //turn right
      Serial.print("Current:");
      Serial.print(currAngle);
      Serial.print(",Order:");
      Serial.print(orderAngle);
      Serial.println(",Turning Right");      
      motor1.SetTurnDirection(right);
      motor1.Turn();
      
    } else 
    { 
      //turn left
      Serial.print("Current:");
      Serial.print(currAngle);
      Serial.print(",Order:");
      Serial.print(orderAngle);
      Serial.println(",Turning Left");
      motor1.SetTurnDirection(left);
      motor1.Turn();
    }
            
  } 
  
  motor1.Stop(); //if there is no error, stop the motor
    
}

void PrintServoPosition(double orderAngle)
{
  double potRest = (double)analogRead(potPin)/1023 * 47;
  
  double currAngle = map(potRest,0.64,38,0,180);
  
  Serial.print("Ordered Angle:");
  Serial.print(orderAngle);  
  Serial.print(" ,Position:");
  Serial.println(currAngle);
  
  delay(50);
}



