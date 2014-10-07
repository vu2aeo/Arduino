#include <LiquidCrystal.h>

LiquidCrystal lcd1(10,3,4,5,6,7);

//HARDWARE DECLARATIONS

int modeSelectPin = 3;//analog pin 3 - mode selector pin (4 arm voltage divider)
int resetPin = 2; //digital pin 2 (arduino interrupt 0)- reset push button

int opRegimePin = 4; // analog pin 4 - TEST/ PULSE regime pin (2 arm voltage divider)

int confirmPin = 12;// digital pin 12 - start btn pin in INT modes
int startPin = confirmPin; // digital pin - push btn in MAN mode. Same pin as startPin

int pirPin = 11;// digital pin 11 - output from the PIR

int delayPotPin = 1; // analog pin 2 - delay between pulses in INT mode
int repPotPin = 0; //analog pin 0 - number of reps in INT mode

int thresholdPin = delayPotPin; //analog pin 1 - threshold for LDR
int ldrPin = 2; // analog pin 2 - LDR voltage divider 


int IRLEDPin = 8; // digital pin 8 - output to IR LED
int testLEDPin = 9;// digital pin 9 - output to test LED

int pirOnPin = 13; // digital pin 13 - power on to PIR sensor

//SOFTWARE DECLARATIONS

#define REGIME_THRESHOLD 850 // threshold to switch between TEST/ PULSE regimes

#define LDR_DEFAULT_DELAY 500 // default delay between pulses in LDR mode

#define PIR_DEFAULT_DELAY 500 // default delay between pulses in PIR mode

#define CAMERA_TIMEOUT 3000 // default timeout after which a pulse is txed
#define CAMERA_TIMEOUT 840000 //15 minutes//prevents the camera from switching off to save power
                             
int opMode; // mode of operation 

unsigned long t0, t1; //time counters

enum opMode{NONE,MAN,INT,LDR,PIR};

boolean inTestRegime = true; //are we flashing a test LED or sending an actual IR pulse?

void setup()
{
  digitalWrite(confirmPin,LOW);
  pinMode(resetPin, INPUT);
  pinMode(confirmPin,INPUT);
  pinMode(pirPin, INPUT);
  pinMode(IRLEDPin, OUTPUT);
  pinMode(testLEDPin, OUTPUT);
  pinMode(pirOnPin,OUTPUT);
  
  //attachInterrupt(0,ChangedMode,RISING);//cant use interrupt
  //because i dont have an inverting schmiddt trigger
  
  opMode = MAN; // at startup, MANUAL MODE is always selected
  
  t0 = millis();
  
  //Serial.begin(9600);
  
  lcd1.begin(2,16);
  
}

void loop()
{ 
  //First check if the default camera timeout has elapsed
  //if it has, send a pulse on the IR LED to keep the 
  //camera awake
  
  t1 = millis();
  
  if(t1 - t0 > CAMERA_TIMEOUT)
  {
    pulse(false);
    
    //Serial.println("CAMERA TIMED OUT!");
    
    t0 = t1;
  }
  
  //IF the timeout has not yet expired see which mode
  //we are in....
  
  ChangedMode();
  
  //Determine which regime we are in....TEST or PULSE
  //Serial.print("Op REgime Pin:");
  //Serial.println(analogRead(opRegimePin));
  
  if(analogRead(opRegimePin) > REGIME_THRESHOLD)
  {
  	inTestRegime = true;
  
  } else inTestRegime = false;
  
  //check the operating mode and act accordingly....

	switch (opMode) {
	
	case MAN:
	  {
      	        UpdateLCD(MAN,0,0,0);
      	   
      		if(digitalRead(startPin) == HIGH)
      		{ 
                        //send a pulse
      			pulse(inTestRegime);
                        //Serial.println("Sending Pulse");
      		} 
      
                delay(50);//give a small pause before checking again
                
      	        break;
	}
	case INT:
	{
	       //read the intervalometer parameters
		
		int tDelay = analogRead(delayPotPin)/2;
	 	
	 	int reps = analogRead(repPotPin)/10;

//                        Serial.print("reps:");
//                        Serial.print(reps);
//                        Serial.print(", delay:");
//                        Serial.println(tDelay);
	 
	        UpdateLCD(INT, tDelay, reps, 0);	
	 
  	       if(digitalRead(startPin) == HIGH)
  	       {
  	 	//start the sequence
  
                  for(int i = reps; i > 0; i --)
  	 	    { 
  	 		// send a pulse
  	 		
  	 		pulse(inTestRegime);
  
                        //update LCD
                        
                        UpdateLCD(INT, tDelay, reps, i-1);
  
                        Serial.println("Sending Pulse");
  
  	 		//delay by the required interval
  	 		
  	 		delay(tDelay*1000);
  
  	 	    } 
  	       }
  
              break;
	}
	case LDR:
	{
		//read the threshold and actual LDR pin
		
		int threshold = analogRead(thresholdPin);
		
		int ldrValue = 1023 - analogRead(ldrPin);

//                        Serial.print("LDR:");
//                        Serial.print(ldrValue);
//                        Serial.print(", threshold:");
//                        Serial.println(threshold);

		
		//display on LCD
		
		UpdateLCD(LDR,threshold, ldrValue, 0);
				
		if(ldrValue > threshold)
		{
			//pulse the LED
	 		
	 		pulse(inTestRegime);

                        //Serial.println("Sending Pulse");
			
			//delay for default duration after the pulse
			
			delay(LDR_DEFAULT_DELAY);
		} 
	        break;
        }
	case PIR:
	{
		
		UpdateLCD(PIR,0,0,0);

                //while the PIR Data remains HIGH, keep sending pulses
		
		while (digitalRead(pirPin) == HIGH)
		{
  
                UpdateLCD(PIR,1,0,0);
		
                //Serial.println("Inside PIR Loop");
  
		pulse(inTestRegime);

                //Serial.println("Sending Pulse");

                delay(PIR_DEFAULT_DELAY);
			
		}
                
	        break;
          }
        }//end switch
}

void ChangedMode()
{ 
//     Serial.println();
//     Serial.print("Mode:");
     
     //Read the MODE SELECTOR PIN AND CHANGE THE MODE
      
     float modeValue = analogRead(modeSelectPin);
     
     //Serial.println(modeValue);
 
     if (modeValue > 0 && modeValue < 400)
     {
       //MANUAL MODE SELECTED
       
       opMode = MAN;
       
       //to save power, make sure the PIR sensor is off
       
       digitalWrite(pirOnPin, LOW);
     } 
     else if(modeValue >= 400 && modeValue < 600)
     {
       //INTERVALOMETER MODE SELECTED
       
       opMode = INT;
       
       //to save power, make sure the PIR sensor is off 
       
       digitalWrite(pirOnPin, LOW);
       
     } 
     else if(modeValue >= 600 && modeValue < 820)
     {
       //LDR MODE SELECTED
       
       opMode = LDR;  
       
     //to save power, make sure the PIR sensor is off
       
       digitalWrite(pirOnPin, LOW);
     } 
     else if(modeValue >= 820 && modeValue < 1024)
     {
       //PIR MODE SELECTED
       
       opMode = PIR;
       
       //switch on the PIR sensor
       
       digitalWrite(pirOnPin, HIGH);
     }
     
//     Serial.print(opMode);
//     Serial.print("  ");
            
}

void pulse(boolean inTestRegime)
{
	if (inTestRegime)
			{ 
				//pulse the test LED
                                digitalWrite(testLEDPin, HIGH);
                                delay(250);
                                digitalWrite(testLEDPin,LOW);
                                //Serial.println("TEST PULSE>>>");                                
			} 
			else
			{
				//pulse the IR LED
                                //Serial.println("IR PULSE>>>");
                                SendCommand();
			} 
}

void UpdateLCD(int mode, int v1, int v2, int v3)
{
	lcd1.setCursor(0,0);
	
	switch (opMode)
        {
	
	case MAN:
	       
               ClearLCDScreen();
	       lcd1.print("Mode:Manual");
	       break;
	
	case INT:
	        ClearLCDScreen();
		lcd1.print("Mode:Delay");
		lcd1.setCursor(0,1);
		lcd1.print("T:");
		lcd1.print(v1);
		lcd1.setCursor(6,1);
		lcd1.print("R:");
		lcd1.print(v3);
                lcd1.print("/");
                lcd1.print(v2);
	        break;
	
	case LDR:
	        ClearLCDScreen();
		lcd1.print("Mode:Light");
		lcd1.setCursor(0,1);
		lcd1.print("Set:");
		lcd1.print(v1);
		lcd1.setCursor(9,1);
		lcd1.print("Now:");
		lcd1.print(v2);
                break;
		
	case PIR:
	        ClearLCDScreen();
		lcd1.print("Mode:PIR Motion");
		lcd1.setCursor(0,1);

                if(v1==1)
                {
                  lcd1.setCursor(0,1);
		  lcd1.print("Motion Detect!!!!");
                }
                break;
	}

        //leave the LCD displaying this data for 10 ms
        
        delay(10);	
	
}

void ClearLCDScreen()
{
  lcd1.setCursor(0,0);
  lcd1.print("                ");
  lcd1.setCursor(0,1);
  lcd1.print("                ");
  lcd1.setCursor(0,0);
}

void SendCarrier(int lengthInMicros)
{
  digitalWrite(IRLEDPin, LOW);
  
  int reps = lengthInMicros/26;
  
  for(int i = 0; i < reps; i++)
  {
    digitalWrite(IRLEDPin, HIGH);
    delayMicroseconds(11);
    digitalWrite(IRLEDPin, LOW);
    delayMicroseconds(5);
  }
  
}

void SendCommand()
{
  SendCarrier(2020);
  delay(28);
  SendCarrier(440);
  delayMicroseconds(1600);
  SendCarrier(320);
  delayMicroseconds(3700);
  SendCarrier(480); 
 
  delay(6);
  
  SendCarrier(2020);
  delay(28);
  SendCarrier(440);
  delayMicroseconds(1600);
  SendCarrier(320);
  delayMicroseconds(3700);
  SendCarrier(480); 
  
}

