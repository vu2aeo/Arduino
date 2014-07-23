#include <Servo.h>

int thumbPin = 3;
int indexPin = 5;
int middlePin = 6;
int ringPin = 9;

#define OPEN_FULL 180
#define CLOSE_FULL 0

Servo thumb, index, middle, ring;

void setup()
{
  thumb.attach(thumbPin);
  index.attach(indexPin);
  middle.attach(middlePin);
  ring.attach(ringPin);
}

void runLoopSequence()
{
  thumb.write(OPEN_FULL);
  delay(500);
  thumb.write(CLOSE_FULL);
  delay(500);
  
  index.write(CLOSE_FULL);
  delay(500);
  index.write(OPEN_FULL);
  delay(500);
  
  middle.write(OPEN_FULL);
  delay(500);
  middle.write(CLOSE_FULL);
  delay(500);
  
  ring.write(OPEN_FULL);
  delay(500);
  ring.write(CLOSE_FULL);
  delay(500);
  
}

void runLoopTogether()
{
  thumb.write(OPEN_FULL);
  index.write(CLOSE_FULL);
  middle.write(OPEN_FULL);
  ring.write(OPEN_FULL);
  
  delay(1000);
  
  thumb.write(CLOSE_FULL);
  index.write(OPEN_FULL);
  middle.write(CLOSE_FULL);
  ring.write(CLOSE_FULL);
  
  delay(1000);
  
  
}


void loop()
{
  runLoopSequence();
  
  delay(1000);
  
  runLoopTogether();
  
  delay(1000);
}

