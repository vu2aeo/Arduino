/*RF24 Basic Receiver*/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"


// Set up nRF24L01 radio on SPI bus plus pins 9 & 10 

RF24 radio(9,10);

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

//container to hold the data

float rxData[2];

void setup(void)
{
  //
  // Print preamble
  //

  Serial.begin(57600);
  printf_begin();
  
  SetupReceiver();
}

void SetupReceiver()
{
   // Setup and configure rf radio

  radio.begin();
  
  radio.setDataRate(RF24_2MBPS);//reduce data rate to min
  
  radio.setPALevel(RF24_PA_LOW); //lower the txn power output

  radio.setRetries(15,15);

  radio.setPayloadSize(8);

  radio.openWritingPipe(pipes[1]);
  
  radio.openReadingPipe(1,pipes[0]);

  radio.startListening();

  //radio.printDetails();

}

boolean NewIncomingData()
{
        if(radio.available())
        {
          boolean done = false;
          
          while(!done)
          {
            done = radio.read(rxData,sizeof(rxData));
  
          }
          
          return true;
        } else return false;
}

void loop(void)
{

    // if there is data ready
    
    if(NewIncomingData())
    {
        
        Serial.print("Rx[0]:");
        Serial.print(rxData[0]);
        Serial.print("   Rx[1]:");
        Serial.println(rxData[1]);
    } 
 
}
// vim:cin:ai:sts=2 sw=2 ft=cpp
