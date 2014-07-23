//PIN DESIGNATIONS
//MODE OF OPS

int resetPin = 2; //interrupt digital input to reset mode of ops

int modePin = 0; //analog input to determine mode of ops

//INPUT PINS
////ANALOG INPUT PINS

//int thresholdPin = 3; //analog input for LDR mode
//
//int LDRPin = 5; //analog input of LDR sensor
//
//int intervalPin = 3; //analog input for TIMER mode
//
//int repsPin = 4; //analog input for TIMER mode

////DIGITAL INPUT PINS

int manTriggerPin = 9; //digital input for manual trigger
//
//int testPin = 8; //digital input to determine TEST or PULSE output
//
//int PIRPin = 9; //digital input of PIR sensor

//OUTPUT PINS

//int pulsePin = 5; //digital output for  pulse in ALL modes
//
int testLEDPin = 3; //digital output for testing with LED

//OUTPUT LED PINS

int timerModeLED = 5;
int LDRModeLED = 6;
int PIRModeLED = 7;
int manualModeLED = 8;

//Variable Declarations
boolean lastButton = LOW; //for debouncing manual trigger
boolean currentButton = LOW;//for debouncing manual trigger

int currentMode = 1;

enum currentMode {TIMER, LDR, PIR, MANUAL};

void ChangeMode()
{
  int modeInput = analogRead(modePin);
  Serial.print("Entering Interrupt....Reading:");
  Serial.print(modeInput);
    
  if (modeInput >= 75 && modeInput < 200)
  {
    //the selector switch is in TIMER mode
    currentMode = TIMER;
    //change LED indicators
    digitalWrite(timerModeLED, HIGH);
    digitalWrite(LDRModeLED, LOW);
    digitalWrite(PIRModeLED, LOW);
    digitalWrite(manualModeLED, LOW);
  } 
  else if (modeInput > 200 && modeInput <= 315)
  {
    //the selector switch is in LDR mode
    currentMode = LDR;
    //change LED indicators
    digitalWrite(timerModeLED, LOW);
    digitalWrite(LDRModeLED, HIGH);
    digitalWrite(PIRModeLED, LOW);
    digitalWrite(manualModeLED, LOW);
  }
  else if (modeInput > 315 && modeInput <= 500)
  {
    //the selector switch is in PIR mode
    currentMode = PIR;
    //change LED indicators
    digitalWrite(timerModeLED, LOW);
    digitalWrite(LDRModeLED, LOW);
    digitalWrite(PIRModeLED, HIGH);
    digitalWrite(manualModeLED, LOW);
  }
  else if (modeInput > 500 && modeInput <=700)
  {
    //the selector switch is in MANUAL mode
    currentMode = MANUAL;
    //change LED indicators
    digitalWrite(timerModeLED, LOW);
    digitalWrite(LDRModeLED, LOW);
    digitalWrite(PIRModeLED, LOW);
    digitalWrite(manualModeLED, HIGH);
  }
}

void BlinkTestLED(int reps, int interval)
{
  for (int i =0; i < reps; i++)
  {
      digitalWrite(testLEDPin, HIGH);
      delay(50);
      digitalWrite(testLEDPin, LOW);
      delay(interval);
  }
  
}


boolean Debounce(boolean last)
{
  boolean current = digitalRead(manTriggerPin);
  
  if (last!=current)
  {
    delay(5);
    current = digitalRead(manTriggerPin);
  }
  
  return current;
}

void setup()
{
  //Serial.begin(9600);
  pinMode(resetPin, INPUT);
  pinMode(timerModeLED, OUTPUT);
  pinMode(LDRModeLED, OUTPUT);
  pinMode(PIRModeLED, OUTPUT);
  pinMode(manualModeLED, OUTPUT);
  pinMode(manTriggerPin, INPUT);
  pinMode(testLEDPin, OUTPUT);
  digitalWrite(testLEDPin, LOW);
//  pinMode(pulsePin, OUTPUT);
//  pinMode(PIRPin, INPUT);
  attachInterrupt(0,ChangeMode, RISING);
}

void loop()
{
//  if (digitalRead(resetPin) == HIGH)
//  {
//    Serial.print("RESET IS HIGH");
//  }
  //Serial.println(analogRead(modePin));
  //delay(500);
  //Serial.print("Current Mode:");
  if (currentMode == TIMER)
  {
      Serial.println("Running TIMER mode...");
//    //analyse the settings
//    
//    int interval = analogRead(intervalPin);
//    
//    int reps = analogRead(repsPin);
//    
//    //send the signal
//    if (digitalRead(testPin) == HIGH)
//    {
//      //send the pulse to the IR LED
//      
//    }
//    else
//    {
//      //send the pulse to the TEST LED
//      
//    }
  } 
  else if (currentMode == LDR)
  {
    //analyse the settings
      Serial.println("Running LDR mode...");
//    int threshold = analogRead(thresholdPin);
//    
//    int sensorVal = analogRead(LDRPin);
//    
//    if (sensorVal > threshold)
//    {
//      //send the signal
//      if (digitalRead(testPin) == HIGH)
//      {
//        //send the pulse to the IR LED
//      }
//      else
//      {
//        //send the pulse to the TEST LED
//      }
//    }
    
    
  } 
    else if (currentMode == PIR)
  {
    //analyse the settings
      Serial.println("Running PIR mode...");
//    if (digitalRead(PIRPin) == HIGH)
//    {
//      //send the signal
//      if (digitalRead(testPin) == HIGH)
//      {
//        //send the pulse to the IR LED
//      }
//      else
//      {
//        //send the pulse to the TEST LED
//      }
//      
//    }
  } 
    else if (currentMode == MANUAL)
  {
      currentButton = Debounce(lastButton);
  
    if(lastButton == LOW && currentButton == HIGH)
    {
      //send the signal
      BlinkTestLED(3,100);
////      if (digitalRead(testPin) == HIGH)
////      {
////        //send the pulse to the IR LED
////      }
////      else
////      {
//        //  send the pulse to the TEST LED
////      }
    }
    else
    {
      digitalWrite(testLEDPin, LOW);
    }
    
    lastButton = currentButton;
       
    //analyse the settings
    Serial.println("Running MANUAL mode...");
//    while (digitalRead(manTriggerPin) == HIGH)
//    {
//      digitalWrite(testLEDPin,HIGH);
//      delay(200);
//      digitalWrite(testLEDPin,LOW);
//      delay(200);
//    } 
  
       
  } 
  
}


