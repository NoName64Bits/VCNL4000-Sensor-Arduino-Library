#ifndef VCNL4000_h
#define VCNL4000_h

#include <Arduino.h>

class VCNL{
	public:
		VCNL(int brg);
		unsigned int readProximity();
		unsigned int readAmbient();
		bool init();
 };
 
#endif