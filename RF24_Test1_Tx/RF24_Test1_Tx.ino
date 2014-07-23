#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

//NRF24 Transmitter on Arduino UNO

int cePin = 9;
int csPin = 10;

//NRF24 Transmitter on Arduino Mega
//
//int cePin = 40;
//int csPin = 53;

int joystick[2];
 
RF24 radio(cePin,csPin);
 
const uint64_t pipe = 0xE8E8F0F0E1LL;
 
void setup(void)
{
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
}
 
void loop(void)
{
  joystick[0] = 31;//analogRead(A0);
  joystick[1] = 42;//analogRead(A1);
  
  radio.write(joystick, sizeof(joystick));
  
  //delay(10);
 
}


