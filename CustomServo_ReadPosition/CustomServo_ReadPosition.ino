int potPin = 4;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
    
  PrintServoPosition();
  
}

void PrintServoPosition()
{
  double potRest = (double)analogRead(potPin)/1023 * 47;
  
  double currAngle = map(potRest,0.64,38,0,180);
  
  Serial.print("Pot Reading:");
  Serial.print(potRest);  
  Serial.print(" ,Position:");
  Serial.println(currAngle);
  
  delay(50);
}



