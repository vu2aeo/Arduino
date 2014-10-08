/*RF24 Basic Receiver*/
/*Adapted from J Coliz's superb RF24 library*/

/*
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10 

RF24 radio(9,10);

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipe = 0xF0F0F0F0E1LL;

//container to hold the data

float rxData[2];

void setup(void)
{

  Serial.begin(57600);
  
  printf_begin();
    
  SetupReceiver();
}

void SetupReceiver()
{
   // Setup and configure rf radio

  radio.begin();
  
  radio.setDataRate(RF24_2MBPS);//data rate
  
  radio.setPALevel(RF24_PA_MAX); //txn power output

  radio.setRetries(15,15);

  radio.setPayloadSize(32);
  
  radio.setChannel(100);//set the channel to use

  radio.openReadingPipe(1,pipe);

  radio.startListening();

  radio.printDetails();

}

boolean NewIncomingData()
{
        boolean done = false;
          
        if(radio.available())
        {
          while(!done)
          {
            done = radio.read(rxData,sizeof(rxData));
  
          }
        } 
        
        return done;
}

void loop(void)
{

    // if there is new data available...
    
    if(NewIncomingData())
    {
        //do something with the incoming data packet 
        
        Serial.print("Rx[0]:");
        Serial.print(rxData[0]);
        Serial.print("   Rx[1]:");
        Serial.println(rxData[1]);
    } 
 
}

