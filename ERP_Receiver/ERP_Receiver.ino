#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "bomotorpair.h"


//NRF24 Receiver on Arduino Mega

int cePin = 40;
int csPin = 53;

//create BOMotorPair

int m1p1 = 12;
int m1p2 = 13;
int m1PWM = 14;

int m2p1 = 20;
int m2p2 = 21;
int m2PWM = 22;

BOMotorPair ERP_Drive = BOMotorPair(m1p1, m1p2, m1PWM, m2p1, m2p2, m2PWM);

 
int motorSpd[2];
 
RF24 radio(cePin,csPin);

const uint64_t pipe = 0xE8E8F0F0E1LL;
 
void setup(void)
{
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
}
 
void loop(void)
{
  if ( radio.available() )
  {
    // Dump the payloads until we've gotten everything
    bool done = false;
    while (!done)
    {
      // Fetch the payload, and see if this was the last one.
      done = radio.read(motorSpd, sizeof(motorSpd));
      
      //write to serial monitor for debugging
      Serial.print(motorSpd[0]);
      Serial.print("   ");
      Serial.println(motorSpd[1]);
      
      //turn the motors
      
      //ERP_Drive.MoveWheelsIndependently(motorSpd[0],motorSpd[1]);
    }
  }
}

