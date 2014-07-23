//L293D motor control

int m1Pin1 = 8;
int m1Pin2 = 9;
int m2Pin1 = 10;
int m2Pin2 = 11;

int motionState = 0;

enum motionState{forward, reverse, tRight, tLeft, stopped};

void setup()
{
  pinMode(m1Pin1, OUTPUT);
  pinMode(m1Pin2, OUTPUT);
  pinMode(m2Pin1, OUTPUT);
  pinMode(m2Pin2, OUTPUT);
}

void loop()
{
  //go forward at gradually increasing speed
  
  for (int i =0; i< 256; i++)
  {
    digitalWrite(m1Pin1, LOW);
    analogWrite(m1Pin2, i);
    delay(20);
  }
  
  // reduce forward speed to zero
    for (int i 255 ; i>=0; i--)
  {
    digitalWrite(m1Pin1, LOW);
    analogWrite(m1Pin2, i);
    delay(20);
  }
  
  //go reverse at gradually increasing speed
  
    for (int i =0; i< 256; i++)
  {
    digitalWrite(m1Pin2, LOW);
    analogWrite(m1Pin1, i);
    delay(20);
  }
  
  // reduce forward speed to zero
    for (int i 255 ; i>=0; i--)
  {
    digitalWrite(m1Pin2, LOW);
    analogWrite(m1Pin1, i);
    delay(20);
  }
  
  
}

