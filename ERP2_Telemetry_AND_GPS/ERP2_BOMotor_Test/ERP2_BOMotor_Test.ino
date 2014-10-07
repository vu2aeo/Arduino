#include "bomotorpair.h"

//create BOMotorPair

int m1p1 = 12;
int m1p2 = 13;
int m1PWM = 14;

int m2p1 = 20;
int m2p2 = 21;
int m2PWM = 22;

BOMotorPair ERP_Drive = BOMotorPair(m1p1, m1p2, m1PWM, m2p1, m2p2, m2PWM);

 
int motorSpd[2];
 
void setup(void)
{
}
 
void loop(void)
{
      //turn the motors in all configurations...
      
      int pauseTime = 1000;
      
      motorSpd[0] = 255; motorSpd[1] = 255;
      
      ERP_Drive.MoveWheelsIndependently(motorSpd[0],motorSpd[1]);
      
      delay(pauseTime);
      
      ERP_Drive.Stop();
      
      delay(pauseTime);
      
      motorSpd[0] = -255; motorSpd[1] = -255;
      
      ERP_Drive.MoveWheelsIndependently(motorSpd[0],motorSpd[1]);
      
      delay(pauseTime);
      
      ERP_Drive.Stop();
      
      delay(pauseTime);
      
      motorSpd[0] = -255; motorSpd[1] = 255;
      
      ERP_Drive.MoveWheelsIndependently(motorSpd[0],motorSpd[1]);
      
      delay(pauseTime);
      
      ERP_Drive.Stop();
      
      delay(pauseTime);
      
      motorSpd[0] = 255; motorSpd[1] = -255;
      
      ERP_Drive.MoveWheelsIndependently(motorSpd[0],motorSpd[1]);
      
      delay(pauseTime);
      
      ERP_Drive.Stop();
      
      delay(pauseTime);
      
    }
  }
}

