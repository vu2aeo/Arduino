#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

//NRF24 Receiver on Arduino Mega

int cePin = 40;
int csPin = 53;

//NRF24 Receiver on Arduino UNO

//int cePin = 9;
//int csPin = 10;

 
int joystick[2];
 
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
      done = radio.read( joystick, sizeof(joystick) );
      Serial.print(joystick[0]);
      Serial.print("   ");
      Serial.println(joystick[1]);
    }
  }
}

