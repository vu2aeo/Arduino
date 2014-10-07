#include <Servo.h>

Servo servo1;
Servo servo2;

int servo1Pin = 11;
int servo2Pin = 10;

void setup(){
servo1.attach(servo1Pin);
servo2.attach(servo2Pin);

}

void loop()
{
  for(int i = 0; i<=150; i+=30)
  {
    servo1.write(i);
    servo2.write(150);
    delay(1000);
    servo2.write(60);
    delay(1000);
    delay(100);
  }
  
  delay(5000);
  
  for(int i = 150; i>=0; i-=30)
  {
    servo1.write(i);
    servo2.write(150);
    delay(1000);
    servo2.write(60);
    delay(1000);
    delay(100);
 
  }
  
  delay(5000);



}
