 #include <math.h>
 
 void setup()  
 {  
  pinMode(7,INPUT); // TSOP 1738 is connected on pin 7  
  Serial.begin(9600);  
 }  
 void loop()  
 {  
  int time = pulseIn(7,LOW);  
  
  if(time > 2000) // Checking if the Start Bit has been received. Start Bit Duration is 2.4ms  
  {  
     long decodeValue = 0;
     
     for(int counter1=0;counter1<50;counter1++) //loop to receive upto 200 bits 
     {  
      int pulseTime = pulseIn(7,HIGH);
      
      if(pulseTime < 8000) // TSOP1738 is HIGH while idling. 
      {  
        
          if (pulseTime > 1000) // anything above 1 ms is counted as one...otherwise it is a zero
          {
              Serial.print("1");  
 
              if (counter1>16)
             {
                 decodeValue+=pow(2,counter1);
             }
             
          }  
          else
          {
            Serial.print("0");
          }
      
      }  else 
      {
        Serial.print(":No of bits:");
        Serial.print(counter1);
        Serial.print("Decoded:");
        Serial.print(decodeValue);
        Serial.println();
        break; //if the TSOP 1738 has been idling for over 10ms,  command is over. exit the for loop.
      }
    } 
  }
  
 delay(1000);  
 }  

