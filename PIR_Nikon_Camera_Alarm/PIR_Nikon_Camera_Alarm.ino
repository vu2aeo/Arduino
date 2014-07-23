int ledPin = 13;
int outPin = 8;
int pirPin = 10;

void setup()
{
  pinMode(ledPin,OUTPUT);
  pinMode(outPin, OUTPUT);
  pinMode(pirPin,INPUT);
}

void loop()
{
  while(digitalRead(pirPin) == HIGH)
  {
    digitalWrite(ledPin, HIGH);
    
    DoPhotoLoop(2,1000);
  }
  digitalWrite(ledPin, LOW);
  
}

void SendPulse(int pulseWidth)
{
  //pulseWidth must be in microseconds
  
  int reps = pulseWidth/23.6;
  
  for(int i=0;i<=reps;i++)
  {
    digitalWrite(outPin,HIGH);
    delayMicroseconds(11);
    digitalWrite(outPin,LOW);
    delayMicroseconds(5);
  }
  
}

void SendSequence()
{
  
  for(int i=0;i<2;i++)
  {
    //pulse for 2.0 millis
    SendPulse(2000);
    //delay for 27.8 millis
    //using a combination of delay() and delayMicroseconds()
    delay(27);
    delayMicroseconds(800);
    //on pulse for 0.5 millis
    SendPulse(500);
    //delay for 1.5 millis
    delayMicroseconds(1500);
    //on pulse for 0.5 millis
    SendPulse(500);
    //delay for 3.5 millis
    delayMicroseconds(3500);
    //send pulse for 0.5 millis
    SendPulse(500);
    if(i<1)
    {
      delay(63);
    }
  }
}

void DoPhotoLoop(int reps, int timeInterval)
{
  //timeInterval in millis
  for(int i=0;i<=reps;i++)
  {
    SendSequence();
  }
  delay(timeInterval);
}




