#include <SoftwareSerial.h>

// Include the Wire library so we can start using I2C.
#include <Wire.h>
// Include the Love Electronics ADXL345 library so we can use the accelerometer.
#include <ADXL345.h>

// Declare a global instance of the accelerometer.
ADXL345 accel;

// Set up a pin we are going to use to indicate our status using an LED.
int statusPin = 13; // I'm using digital pin 2.


#define NO_OF_FIELDS 2

SoftwareSerial mySerial(8,7); // RX, TX

float txData[NO_OF_FIELDS];

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(38400);

  // set the data rate for the SoftwareSerial port
  mySerial.begin(38400);
  
   // Start the I2C Wire library so we can use I2C to talk to the accelerometer.
  Wire.begin();
  
  // Ready an LED to indicate our status.
  pinMode(statusPin, OUTPUT);
  
  // Create an instance of the accelerometer on the default address (0x1D)
  accel = ADXL345();
  
  // Check that the accelerometer is infact connected.
  if(accel.EnsureConnected())
  {
    Serial.println("Connected to ADXL345.");
    //digitalWrite(statusPin, HIGH); // If we are connected, light our status LED.
      // Set the range of the accelerometer to a maximum of 2G.
  accel.SetRange(2, true);
  // Tell the accelerometer to start taking measurements.
  accel.EnableMeasurements();
  }
  else 
  {
    Serial.println("Could not connect to ADXL345.");
    digitalWrite(statusPin, LOW); // If we are not connected, turn our LED off.
  }
  
}


void SendData(float txData[])
{
  int checkSum;//create a checksum
  
  mySerial.print("***");//send data wrapper
  
  for (int i=0;i<NO_OF_FIELDS;i++)
  {
    checkSum+=txData[i];
    mySerial.print(txData[i]);
    mySerial.print(",");
  }
  
  //send checksum
  mySerial.print(checkSum);
  mySerial.print("&&&");//sebdend wrapper
}

void ParseAndSendMotorCommands(float x, float y)
{
  
//  Serial.print("left:");
//  Serial.print(lval);
//  Serial.print("    right:");
//  Serial.println(rval);
    
  //write to serial treansmitter
  
  
  
}

void loop() // run over and over
{

    if(accel.IsConnected) // If we are connected to the accelerometer.
  {
    // Read the raw data from the accelerometer.
    AccelerometerRaw raw = accel.ReadRawAxis();
    //This data can be accessed like so:
    int xAxisRawData = raw.XAxis;
    
    // Read the *scaled* data from the accelerometer (this does it's own read from the accelerometer
    // so you don't have to ReadRawAxis before you use this method).
    // This useful method gives you the value in G thanks to the Love Electronics library.
    AccelerometerScaled scaled = accel.ReadScaledAxis();
    // This data can be accessed like so:
    float xAxisGs = scaled.XAxis;
    
    // We output our received data.
    Output(raw, scaled);
  }
  
  delay(50);
 
}

void Output(AccelerometerRaw raw, AccelerometerScaled scaled)
{
  
   float spd;
   
   float offset;
   
   float lval, rval;
   
  
   spd = (float)raw.XAxis * 2;
   
   offset = (float)raw.YAxis * 2;
   
   if (spd>=255) spd = 255;
   
   if (offset>=255) offset = 255;
   
   spd = spd/255;
   
   if (offset<0 && offset < -50)
  {
        rval = 255 * spd;//right motor normal
    
    //reverse the left motor
    
    lval = (offset - 255) * spd;
  } 
  
     else if (offset > 0 && offset > 50)
  {
        lval = 255 * spd;//left motor normal
    
    //reverse the right motor
    
    rval = (offset + 255) * spd * -1;
  } 
    else //keep both motors at full power
  
  {
    lval = 255 * spd;
    
    rval = 255 * spd;
  }
  
  
   
   txData[0] = lval;
   txData[1] = rval;
   
   SendData(txData);
   
      // Tell us about the raw values coming from the accelerometer.
   Serial.print("Raw:\t");
   Serial.print(txData[0]);
   Serial.print("   ");   
   Serial.println(txData[1]);   

}
