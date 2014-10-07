/*RF24 Basic Receiver*/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10 

RF24 radio(9,10);

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

//container to hold the data

float rxData[2];

void setup(void)
{

  Serial.begin(57600);
    
  SetupReceiver();
}

void SetupReceiver()
{
   // Setup and configure rf radio

  radio.begin();
  
  radio.setDataRate(RF24_2MBPS);//data rate
  
  radio.setPALevel(RF24_PA_HIGH); //txn power output

  radio.setRetries(15,15);

  radio.setPayloadSize(32);
  
  radio.setChannel(100);//set the channel to use

  radio.openWritingPipe(pipes[1]);
  
  radio.openReadingPipe(1,pipes[0]);

  radio.startListening();

  //radio.printDetails();

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

