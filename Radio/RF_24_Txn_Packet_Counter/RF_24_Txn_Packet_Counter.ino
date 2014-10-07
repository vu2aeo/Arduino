/*RF24 Basin Transmitter*/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10 

RF24 radio(9,10);

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

//container for the data

float txData[2];

//success and fail counters

float pktOK, pktFail;

void setup(void)
{

  Serial.begin(57600);
    
  SetupTransmitter();
  
  pktOK = 0;
  
  pktFail = 0;

}

void SetupTransmitter()
{

  // Setup and configure rf radio

  radio.begin();
  
  radio.setDataRate(RF24_2MBPS);//data rate
  
  radio.setPALevel(RF24_PA_HIGH); //txn power output

  radio.setRetries(15,15);

  radio.setPayloadSize(32);
  
  radio.setChannel(100); //set the channel to use
    
  radio.openReadingPipe(1,pipes[1]);

  radio.startListening();

  //radio.printDetails();
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
      //digitalWrite(LEDPin,HIGH);
      //delay(15);
      pktOK++;
      
     }
    else
    {
      //Serial.println("failed.");
      //turn off the green LED to show that the link is down
      //digitalWrite(LEDPin,LOW);
      //delay(15);
      pktFail++;
    }
    
    //turn off the green status LED
    //digitalWrite(LEDPin,LOW);
    //delay(15);
    
      Serial.print("Success Count:");
      Serial.print(pktOK);
      Serial.print("   Fail Count:");
      Serial.println(pktFail);

    // Try again later
    delay(2);

}

