#include <Wire.h>
#include <VCNL4000.h>

int brightness = 20; //from 1 to 20
//the current that will be drawn by the ir emittr will be (brightness * 10) mA

VCNL myvcnl(brightness); //this will create a instance of the sensor, it takes 1 parameter (the brightness)

void setup() {
  Serial.begin(9600);
  if(myvcnl.init()){//the initializer
   Serial.println("OK"); //if it returns true, this means all is ok
  }
  else {
   Serial.println("Your sensor Bro! Is not working!");// if not, eee... you know, your problem
  }
}

void loop() {
   Serial.print(myvcnl.readProximity()); Serial.print(" - "); Serial.println(myvcnl.readAmbient());
   //thoose functions will return integers of the reading of sensors, and will print them on serial
   delay(1000);
}