int IN1=5;
int IN2=6;
int ENA=3;
void setup()
{
 pinMode(IN1,OUTPUT);
 pinMode(IN2,OUTPUT); 
 pinMode(ENA,OUTPUT); 
}
void loop()
{
 digitalWrite(IN1,LOW);// rotate forward
 digitalWrite(IN2,HIGH);
 for (int i = 0; i< 256; i++)
  {  
   analogWrite(ENA, i);// motor speed  
   delay(20);
  }
  
 digitalWrite(IN1,HIGH);// rotate reverse
 digitalWrite(IN2,LOW);
 
 for (int i = 255; i > 0; i--)
  {  
   analogWrite(ENA, i);// motor speed  
   delay(20);
  }

}
