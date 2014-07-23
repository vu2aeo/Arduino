int switchPin = 2;
int ledPin = 11;

boolean lastButton = LOW;
boolean currentButton = LOW;
boolean ledOn = false;

void setup()
{
  pinMode(switchPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

boolean Debounce(boolean last)
{
  boolean current = digitalRead(switchPin);
  
  if (last!=current)
  {
    delay(5);
    current = digitalRead(switchPin);
  }
  
  return current;
}

void loop()
{
  currentButton = Debounce(lastButton);
  
  if(lastButton == LOW && currentButton == HIGH)
  {
    ledOn = !ledOn;
  }
  lastButton = currentButton;
  digitalWrite(ledPin, ledOn);
  
}



