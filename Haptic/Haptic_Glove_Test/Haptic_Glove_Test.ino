
int sensorPin[5] = {0,1,2,3,4};

int sensorMaxVal[5] = {0,0,0,0,0};

int sensorMinVal[5] = {0,0,0,0,0};

int sensorFlexVal[5] = {0,0,0,0,0};

int t0;

void setup()
{
  
  Serial.begin(9600);
  
  t0 = millis();
}

void loop()
{
  // run calibration for 10 seconds
  
  Serial.println("Calibrating");
  
  sensorMinVal[0] = analogRead(sensorPin[0]);
  
  while (millis() - t0 < 10000)
  {
      int readVal = analogRead(sensorPin[0]);
      
      if (readVal >= sensorMaxVal[0])
      {
        sensorMaxVal[0] = readVal;
      }
      else if (readVal <= sensorMinVal[0])
      {
        sensorMinVal[0] = readVal; 
      }
      
      Serial.print("Max:");
      Serial.print(sensorMaxVal[0]);
      Serial.print(",   Min:");
      Serial.println(sensorMinVal[0]);
  
  }
    
//    Read Continuously

while (millis() - t0 > 10000)
{
  int readVal = analogRead(sensorPin[0]);
  
  constrain(readVal, sensorMinVal[0], sensorMaxVal[0]);

  float percent = 1.2 * abs((readVal - sensorMinVal[0]) * 100/(sensorMaxVal[0] - sensorMinVal[0]));

  Serial.print("Flexing To:");
  Serial.print(percent);
  Serial.println(" percent.");

delay(100);

}



}


