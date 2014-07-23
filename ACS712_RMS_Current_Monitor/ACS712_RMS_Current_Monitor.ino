//defines

#define CALIB_PERIOD 2000;
#define CYCLE_FREQ 50

//constants

int sensorPin = 0;
int resetPin = 4;
int restartPin = 5;
int mode5APin = 6;
int mode20APin = 7;
int mode;
float convConst = 5/185;
int calibPeriod = 2000;
float calibErr = 0;
float rmsI, rmsAH, rmsPower;

enum mode {Amp5, Amp20};

void setup()
{
  Serial.begin(115200);
//  attachInterrupt(resetPin,ResetDevice,RISING);
//  attachInterrupt(restartPin, RestartDevice, RISING);
  Serial.println("Starting.......");
  Serial.println(analogRead(sensorPin));
  RestartDevice();
  Calibrate();
}

void loop()
{

  
}

boolean Debounce(boolean last)
{
  boolean current = digitalRead(resetPin);
  
  if (last!=current)
  {
    delay(5);
    current = digitalRead(resetPin);
  }
  
  return current;
}

void ResetDevice()
{
  if (Debounce(LOW) == HIGH)
  {
    if (digitalRead(mode5APin) == HIGH)
    {
	//set up for 5A sensor
	sensorPin = 0;
	convConst = 5/185;
	mode = Amp5;
    }
    else if (digitalRead(mode20APin) == HIGH)
    {
	//set up for 20A sensor
	sensorPin = 1;
	convConst = 5/185;
	mode = Amp20;
    }
  }
		
  Calibrate();
		
  RestartDevice();
}

void RestartDevice()
{
  rmsI = 0;
  rmsAH = 0;
  rmsPower = 0;
}

void Calibrate()
{
  
  //find calibration error
  
  Serial.println("Calibrating......");
  
  float iNow, sum;
  
  iNow = 0;
  
  sum = 0;
		
  unsigned long t0 = micros();
		
    for (int i = 0; i < 100; i++)//take 200 readings
      {
	  Serial.println("Taking a Reading...");
	  float reading = analogRead(sensorPin);
          Serial.println(reading);
  
		
          iNow = (reading - 512) * 0.02703;
          
              Serial.print("I reading:");
              
              Serial.println(iNow);
				
	  sum += iNow * iNow;
		
	while (micros() - t0 < 100)
	{
	  //wait 100 microseconds between readings
	}
				
	t0 = micros();						
      }
    
    calibErr = sqrt(sum/100);
    
    Serial.print("\tRMS Calibration Current Error:");
    Serial.println(calibErr);
	
}
