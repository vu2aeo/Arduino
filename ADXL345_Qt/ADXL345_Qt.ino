// Include the Wire library so we can start using I2C.
#include <Wire.h>
// Include the Love Electronics ADXL345 library so we can use the accelerometer.
#include <ADXL345.h>

// Declare a global instance of the accelerometer.
ADXL345 accel;

// Set up a pin we are going to use to indicate our status using an LED.
int statusPin = 13; // I'm using digital pin 2.

void setup()
{
  // Begin by setting up the Serial Port so we can output our results.
  Serial.begin(2400);
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

void loop() 
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
}

void Output(AccelerometerRaw raw, AccelerometerScaled scaled)
{
   // Tell us about the raw values coming from the accelerometer.
//   Serial.print(raw.XAxis);
//   Serial.print(",");   
//   Serial.print(raw.YAxis);
//   Serial.print(",");   
//   Serial.print(raw.ZAxis);
   
   
   // Tell us about the this data, but scale it into useful units (G).
//   Serial.print("   \tScaled:\t");
   Serial.print(scaled.XAxis);
   Serial.print(",");   
   Serial.print(scaled.YAxis);
   Serial.print(",");   
   Serial.print(scaled.ZAxis);
   Serial.print(",");
   Serial.print("&");
   delay(50);
}
