int IN1=3;
int IN2=4;
int ENA1=5;

int IN3 =7;
int IN4 = 8;
int ENA2 = 6;
void setup()
{
 pinMode(IN1,OUTPUT);
 pinMode(IN2,OUTPUT); 
 pinMode(ENA1,OUTPUT);

 pinMode(IN3,OUTPUT);
 pinMode(IN4,OUTPUT); 
 pinMode(ENA2,OUTPUT); 
}
void loop()
{
  //GO FORWARD
  
 digitalWrite(IN1,LOW);// rotate forward
 digitalWrite(IN2,HIGH);
 digitalWrite(IN3,LOW);// rotate forward
 digitalWrite(IN4,HIGH);
 
 MoveRobot(255, 2);
  
  //GO REVERSE
  
 digitalWrite(IN1,HIGH);// rotate reverse
 digitalWrite(IN2,LOW);
 digitalWrite(IN3,HIGH);// rotate reverse
 digitalWrite(IN4,LOW);
 
 MoveRobot(255, 2);
  
    //TURN RIGHT
  
 digitalWrite(IN1,LOW);// rotate reverse
 digitalWrite(IN2,HIGH);
 digitalWrite(IN3,HIGH);// rotate reverse
 digitalWrite(IN4,LOW);
 
 MoveRobot(255, 2);
  
      //TURN RIGHT
  
 digitalWrite(IN1,HIGH);// rotate reverse
 digitalWrite(IN2,LOW);
 digitalWrite(IN3,LOW);// rotate reverse
 digitalWrite(IN4,HIGH);
 
 MoveRobot(255, 2);

}

void MoveRobot(int motorSpeed, int tSec)
{
   analogWrite(ENA1, motorSpeed);// motor speed  
   analogWrite(ENA2, motorSpeed);// motor speed  
   delay(tSec * 1000);
}

