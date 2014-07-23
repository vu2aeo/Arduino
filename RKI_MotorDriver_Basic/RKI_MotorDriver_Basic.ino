int m1 = 3;

int m2 = 5;




void setup()
{
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
}

void loop()
{
//    digitalWrite(m1,LOW);
//    digitalWrite(m2,HIGH);

for(int i =0 ; i< 256; i++)
{
  analogWrite(m1,i);
  
  delay(20);
}


}

