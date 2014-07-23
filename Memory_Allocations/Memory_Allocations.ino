int dataInt;
unsigned int dataUint;
unsigned long dataL;
unsigned long long dataLL;
float dataF;
char dataCh;

void setup()
{
  Serial.begin(9600);
  Serial.print("Int:");   Serial.println(sizeof(dataInt));
  Serial.print("unsigned int:");   Serial.println(sizeof(dataUint));
  Serial.print("unsigned long:");   Serial.println(sizeof(dataL));  
  Serial.print("unsigned long long:");   Serial.println(sizeof(dataLL));
  Serial.print("Float:");   Serial.println(sizeof(dataF));
  Serial.print("Char:");   Serial.println(sizeof(dataCh));
}

void loop()
{
}

