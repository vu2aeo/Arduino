#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "bomotorpair.h"
#include <LiquidCrystal.h>

// select the pins used on the LCD panel
//RS = Pin 8
//Enable = Pin 9
//D4 - D5 = Pins 4,5,6,7
//LiquidCrystal lcd1(8, 9, 4, 5, 6, 7);

//Setup NRF24 Receiver on Arduino 

int cePin = 9;
int csPin = 10;

//create BOMotorPair

//int m1p1 = 12;
//int m1p2 = 13;
//int m1PWM = 14;
//
//int m2p1 = 20;
//int m2p2 = 21;
//int m2PWM = 22;

//BOMotorPair ERP2_Drive = BOMotorPair(m1p1, m1p2, m1PWM, m2p1, m2p2, m2PWM);

//radio connect status LED

int LEDPin = 5;
 
float motorSpd[2];
 
RF24 radio(cePin,csPin);

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipe = 0xF0F0F0F0E1LL;
 
void setup(void)
{
  Serial.begin(9600);
  
  SetupReceiver();
  
  //lcd1.begin(16,2);
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

  //radio.printDetails();

}

boolean NewIncomingData()
{
        boolean done = false;
          
        if(radio.available())
        {
          while(!done)
          {
            done = radio.read(motorSpd,sizeof(motorSpd));
  
          }
        } 
        
        return done;
}


//void UpdateLCD(int* motorCmd)
//{
//  lcd1.setCursor(0,1);
//  lcd1.print(motorCmd[0]);
//  lcd1.setCursor(0,10);
//  lcd1.print(motorCmd[1]);
//}
 
void loop(void)
{
  if ( NewIncomingData() )
  {
          
    Serial.print("Received Motor Commands, LEFT:");
    Serial.print(motorSpd[0]);
    Serial.print("\t Right:");
    Serial.println(motorSpd[1]);
    
    digitalWrite(LEDPin,HIGH);
  
  } else digitalWrite(LEDPin,LOW);
    
    //write to serial monitor for debugging
//    Serial.print("Received Motor Commands, LEFT:");
//    Serial.print(motorSpd[0]);
//    Serial.print("\t Right:");
//    Serial.println(motorSpd[1]);
    
    //Show motor commands on the LCD Panel 
    
    //UpdateLCD(motorSpd);
    
    //turn the motors
      
    //ERP2_Drive.MoveWheelsIndependently(motorSpd[0],motorSpd[1]);
  
}

