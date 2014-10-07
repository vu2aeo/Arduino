#include "qttalker.h"

QtTalker line1(115200);

  float outData[3];
  
  float inData[3];

void setup()
{
  line1.Connect();
   
}

void loop()
{
    
  if(line1.NewDataAvailable())
  {
    
    //get new data
    line1.GetIncomingData(inData);
    
    //do something with the incoming data..
    
    //send some data back to the Qt source
  
      outData[0] = inData[0];
    
      outData[1] = inData[1];
      
      outData[2] = inData[2];
      
              
      //send data back to source
      line1.SendDataPacketToQt(outData);
  
  } else 
  {
    //prepare some dummy data
    
    outData[0] = millis();
    
    outData[1] = outData[0] + 200;
    
    outData[2] = outData[0] + 400;
    
    //send data back to source
    line1.SendDataPacketToQt(outData);
  }
            
}
