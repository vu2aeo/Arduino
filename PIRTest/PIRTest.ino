int ledPin = 13;
int pirPin = 10;

void setup()
{
  pinMode(ledPin,OUTPUT);
  pinMode(pirPin,INPUT);
}

void loop()
{
  if(digitalRead(pirPin) == HIGH)
  {
    digitalWrite(ledPin, HIGH);
  }
  else digitalWrite(ledPin, LOW);
}


