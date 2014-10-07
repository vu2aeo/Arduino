int triggerPin = 2;
int sonarPin = 3;

void setup()
{
  pinMode(triggerPin, OUTPUT);
  pinMode(sonarPin,INPUT);
  
  Serial.begin(9600);
}

void loop()
{
  //deactivate the sensor
  digitalWrite(triggerPin,LOW);
  delayMicroseconds(2);
  //activate the trigger
  digitalWrite(triggerPin,HIGH);
  //wait for at least 10 usec
  delayMicroseconds(20);
  //send a low to the trigger
  digitalWrite(triggerPin,LOW);
  //read from the sensor
  float t = pulseIn(sonarPin,HIGH);
  
  float d = t/29/200;
  
  if(d<=10)
  {
    Serial.println(d);
  } else
  {
    Serial.println("No Target or Invalid echo!");
  }
  
  delay(20);
  
  
  
}
