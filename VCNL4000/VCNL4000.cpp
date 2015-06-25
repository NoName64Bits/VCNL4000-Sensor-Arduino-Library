#include "VCNL4000.h"
#include "Wire.h"

#define VCNL4000_ADDRESS 0x13  

int bright;

#define COMMAND_0 0x80 
#define PRODUCT_ID 0x81  
#define IR_CURRENT 0x83  
#define AMBIENT_PARAMETER 0x84  
#define AMBIENT_RESULT_MSB 0x85  
#define AMBIENT_RESULT_LSB 0x86  
#define PROXIMITY_RESULT_MSB 0x87  
#define PROXIMITY_RESULT_LSB 0x88  
#define PROXIMITY_FREQ 0x89 
#define PROXIMITY_MOD 0x8A  

VCNL::VCNL(int brg){
	bright = brg;
}
void sendByte(byte address, byte data)
{
  Wire.beginTransmission(VCNL4000_ADDRESS);
  Wire.write(address);
  Wire.write(data);
  Wire.endTransmission();
}

byte receiveByte(byte address)
{
  byte data;
  
  Wire.beginTransmission(VCNL4000_ADDRESS);
  Wire.write(address);
  Wire.endTransmission();
  Wire.requestFrom(VCNL4000_ADDRESS, 1);
  while(!Wire.available())
    ;
  data = Wire.read();

  return data;
}


bool VCNL::init(void){
  Wire.begin(); 
  byte temp = receiveByte(PRODUCT_ID);
  if (temp != 0x11)  
  {
	return false;
  }
  else {
  sendByte(AMBIENT_PARAMETER, 0x0F);  
  sendByte(IR_CURRENT, bright); 
  sendByte(PROXIMITY_FREQ, 2);  
  sendByte(PROXIMITY_MOD, 0x81); 
    return true;
  }
 }
 
 unsigned int VCNL::readProximity()
{
  unsigned int data;
  byte temp;
  
  temp = receiveByte(COMMAND_0);
  sendByte(COMMAND_0, temp | 0x08);
  
  while(!(receiveByte(COMMAND_0)&0x20)) 
    ;  
  data = receiveByte(PROXIMITY_RESULT_MSB) << 8;
  data |= receiveByte(PROXIMITY_RESULT_LSB);
  
  return data;
}

unsigned int VCNL::readAmbient()
{
  unsigned int data;
  byte temp;
  
  temp = receiveByte(COMMAND_0);
  sendByte(COMMAND_0, temp | 0x10);  
  
  while(!(receiveByte(COMMAND_0)&0x40)) 
    ;  
  data = receiveByte(AMBIENT_RESULT_MSB) << 8;
  data |= receiveByte(AMBIENT_RESULT_LSB);
  
  return data;
}
