int outPin = 7;
int pulseWidth=0;

void setup(){

  pinMode(outPin,OUTPUT);
  Serial.begin(9600);
  
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




void loop(){
  
  //shutter control from serial interface

  while (Serial.available()==0);
  
  Serial.read();
  
  //shutter control for time lapse photography

  DoPhotoLoop(1,0);
  
}

