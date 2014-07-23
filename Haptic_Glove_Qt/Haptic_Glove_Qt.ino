
int sensorPin[5] = {0,1,2,3,4};

int sensorVal[5] = {0,0,0,0,0};

int total = 0;

void setup()
{
  
  Serial.begin(9600);

}

void loop()
{
        

      for (int i = 0; i < 5; i ++)
      {
        int readVal = analogRead(sensorPin[i]);
        
        sensorVal[i] = readVal;
        
       }
       
       Serial.print("*");
       
       for (int i = 0; i < 5; i++)
       {
         Serial.print(sensorVal[i]);
         total+= sensorVal[i];
         Serial.print(",");
       }
        Serial.print(total);
        Serial.print(",");
        Serial.print("*");
        Serial.print("&");
        total = 0;
        delay(200);

}


