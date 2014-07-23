//PIN DESIGNATIONS
//MODE OF OPS

int resetPin = 2; //interrupt digital input to reset mode of ops

int modePin = 2; //analog input to determine mode of ops

//INPUT PINS
////ANALOG INPUT PINS

int thresholdPin = 3; //analog input for LDR mode

int LDRPin = 5; //analog input of LDR sensor

int intervalPin = 3; //analog input for TIMER mode

int repsPin = 4; //analog input for TIMER mode

////DIGITAL INPUT PINS

int manTriggerPin = 7; //digital input for manual trigger

int testPin = 8; //digital input to determine TEST or PULSE output

int PIRPin = 9; //digital input of PIR sensor

//OUTPUT PINS

int pulsePin = 5; //digital output for  pulse in ALL modes

int testLedPin = 6; //digital output for testing with LED


int currentMode = 1;

enum currentMode {TIMER, LDR, PIR, MANUAL};

void ChangeMode()
{
  int modeInput = analogRead(modePin);
  
  if (modeInput >= 0 && modeInput < 250)
  {
    //the selector switch is in TIMER mode
    currentMode = TIMER;
  } 
  else if (modeInput > 250 && modeInput <= 500)
  {
    //the selector switch is in LDR mode
    currentMode = LDR;
  }
  else if (modeInput > 500 && modeInput <= 750)
  {
    //the selector switch is in PIR mode
    currentMode = PIR;
  }
  else if (modeInput > 750 && modeInput <=1023)
  {
    //the selector switch is in MANUAL mode
    currentMode = MANUAL;
  }
}

void setup()
{
  pinMode(resetPin, INPUT);
  pinMode(manTriggerPin, INPUT);
  pinMode(testPin, INPUT);
  pinMode(pulsePin, OUTPUT);
  pinMode(PIRPin, INPUT);
  attachInterrupt(resetPin,ChangeMode, RISING);
}

void loop()
{
  if (currentMode == TIMER)
  {
    //analyse the settings
    
    int interval = analogRead(intervalPin);
    
    int reps = analogRead(repsPin);
    
    //send the signal
    if (digitalRead(testPin) == HIGH)
    {
      //send the pulse to the IR LED
      
    }
    else
    {
      //send the pulse to the TEST LED
      
    }
  } 
  else if (currentMode == LDR)
  {
    //analyse the settings
    
    int threshold = analogRead(thresholdPin);
    
    int sensorVal = analogRead(LDRPin);
    
    if (sensorVal > threshold)
    {
      //send the signal
      if (digitalRead(testPin) == HIGH)
      {
        //send the pulse to the IR LED
      }
      else
      {
        //send the pulse to the TEST LED
      }
    }
    
    
  } 
    else if (currentMode == PIR)
  {
    //analyse the settings
    if (digitalRead(PIRPin) == HIGH)
    {
      //send the signal
      if (digitalRead(testPin) == HIGH)
      {
        //send the pulse to the IR LED
      }
      else
      {
        //send the pulse to the TEST LED
      }
      
    }
  } 
    else if (currentMode == MANUAL)
  {
    //analyse the settings
    if (digitalRead(manTriggerPin) == HIGH)
    {
      //send the signal
      if (digitalRead(testPin) == HIGH)
      {
        //send the pulse to the IR LED
      }
      else
      {
        //send the pulse to the TEST LED
      }
    }
   
  } 
  
}


