#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 8); // RX, TX
int counter = 0;

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
 
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);

  Serial.println("Transmitting Data......");

}

void loop() // run over and over
{

  counter++;
  
  mySerial.print("Hello, world?  ");
  mySerial.println(counter);
  delay(250);
  
}
