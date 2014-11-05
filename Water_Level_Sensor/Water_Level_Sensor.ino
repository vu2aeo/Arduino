int levelPin[3];
int LED[2] = {0,1};

int W_LEVEL = 0;

enum W_LEVEL{NIL, LITTLE, MED, FULL};

void setup()
{
  //put all LED pins to output mode
  //and make sure they are tunred off
  for(int i = 0; i < 2; i++)
  {
    pinMode(LED[i],OUTPUT);
    digitalWrite(LED[i],LOW);
  }
  
    digitalWrite(LED[0],HIGH);
    digitalWrite(LED[1],HIGH);
    
    delay(1000);
  
  //flash both LED thrice...to show we are working fine...
  
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(LED[0],HIGH);
    digitalWrite(LED[1],HIGH);
    delay(100);
    digitalWrite(LED[0],LOW);
    digitalWrite(LED[1],LOW);
    delay(100);
    
  }
  
  //Serial.begin(9600);
}

void loop()
{
  //read the levelPins
  levelPin[0] = analogRead(A2);//lowest sensor
  levelPin[1] = analogRead(A3);//upper sensor
  levelPin[2] = analogRead(A1);//middle sensor
  
  //set the W_LEVEL state
  
  if (levelPin[0] < 100) //if the lowest sensor is out of water
  {
    W_LEVEL = NIL;
  } else if (levelPin[0] > 100 && levelPin[2] < 100)
  {
    W_LEVEL = LITTLE;
  } else  if (levelPin[1] > 100) //if the upper sensor is in water
  {
    W_LEVEL = FULL;
  } else  if (levelPin[1] < 100 and levelPin[2] > 100)
  {
    //if the water is between the mid and upper sensor
    W_LEVEL = MED;
  }
  
  //now turn on the LEDs as reqd
  
  switch(W_LEVEL)
  {
    case NIL:
    {
      //turn off both LEDS
      digitalWrite(LED[0],LOW);
      digitalWrite(LED[1],LOW);
      break;
    }
    case LITTLE:
    {
      //turn on the lower LED only
      digitalWrite(LED[0],HIGH);
      digitalWrite(LED[1],LOW);
      break;
    }
    case MED:
    {
      //flash the upper LED only
      digitalWrite(LED[0],HIGH);
      digitalWrite(LED[1],HIGH);
      delay(100);
      digitalWrite(LED[1],LOW);
      delay(100);
      break;
    }
    case FULL:
    {
      digitalWrite(LED[0],HIGH);
      digitalWrite(LED[1],HIGH);
      break;
    }
    default:
    {
      //flash both leds to show something is wrong..
      digitalWrite(LED[0],HIGH);
      digitalWrite(LED[1],HIGH);
      delay(100);
      digitalWrite(LED[0],LOW);
      digitalWrite(LED[1],LOW);
      delay(100);
    }
    
  }
  
  //Send to serial for debugging
  
//  Serial.print("Upper:");
//  Serial.print(levelPin[1]);
//  Serial.print("\t Middle:");
//  Serial.print(levelPin[2]);
//  Serial.print("\t Lower:");
//  Serial.print(levelPin[0]);
//  Serial.print("\t STATUS:");
//  Serial.println(W_LEVEL);
  
  delay(200);
}
