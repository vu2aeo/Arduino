#include <Servo.h>

Servo elbow;

int elbowPin = 5;
int potPin = 1;

void setup()
{
  pinMode(potPin, INPUT);
  Serial.begin(9600);
  elbow.attach(elbowPin);
}

void loop(){
int angle = map(analogRead(potPin),300,1023,0,180);

Serial.println(angle);

elbow.write(angle);

delay(25);

}

