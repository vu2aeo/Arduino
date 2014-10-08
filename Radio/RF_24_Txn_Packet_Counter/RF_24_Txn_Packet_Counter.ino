/*RF24 Basin Transmitter*/

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

//container for the data

float txData[2];

//success and fail counters

float pktOK, pktFail;

//Connect OK LED Pin

int LEDPin = 5;

void setup(void)
{

  Serial.begin(57600);
  
  printf_begin();
    
  SetupTransmitter();
  
  pktOK = 0;
  
  pktFail = 0;
  
  pinMode(LEDPin,OUTPUT);

}

void SetupTransmitter()
{

  // Setup and configure rf radio

  radio.begin();
  
  radio.setDataRate(RF24_2MBPS);//data rate
  
  radio.setPALevel(RF24_PA_MAX); //txn power output

  radio.setRetries(15,15);

  radio.setPayloadSize(32);
  
  radio.setChannel(100); //set the channel to use
  
  radio.openWritingPipe(pipe);
    
  //radio.openReadingPipe(2,pipe);

  radio.startListening();

  radio.printDetails();
}

boolean TransmitData()
{
    radio.stopListening();
    
    bool ok = radio.write(txData, sizeof(txData));
    
    // Now, continue listening
    radio.startListening();
    
    return ok;

}

void loop(void)
{
    // Update the data packet
    
    txData[0] = pktOK;
    
    txData[1] = pktFail;
    
    //Send the Data
    
     if (TransmitData())
    {
      //Serial.println("ok...");
      //light up a green LED to show that the link is active and well
      digitalWrite(LEDPin,HIGH);
      delay(15);
      pktOK++;
      
     }
    else
    {
      //Serial.println("failed.");
      //turn off the green LED to show that the link is down
      digitalWrite(LEDPin,LOW);
      delay(15);
      pktFail++;
    }
    
    //turn off the green status LED
    digitalWrite(LEDPin,LOW);
    delay(15);
    
      Serial.print("Success Count:");
      Serial.print(pktOK);
      Serial.print("   Fail Count:");
      Serial.println(pktFail);

    // Try again later
    delay(200);

}

