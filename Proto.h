#ifndef PROTO_H
#define PROTO_H
#include <cstdio>
#include "mbed.h"

#define LPC_GPIO2_FIOPIN (int *) 0x2009C054
#define LPC_GPIO2_FIODIR (int *) 0x2009C040
#define LPC_PINCON_PINSEL4 (int *) 0x4002C010
#define LPC_PINCON_PINMODE4 (int *) 0x4002C050
	
using namespace std;
	
enum Command {
	ERROR,
	DOT1_ON,
	DOT1_OFF,
	DOT2_ON,
	DOT2_OFF,
	DOT3_ON,
	DOT3_OFF,
	DOT4_ON,
	DOT4_OFF,
	DOT5_ON,
	DOT5_OFF,
	DOT6_ON,
	DOT6_OFF,
	LIGHT_UP,
	LIGHT_DOWN	
};

class Proto {
	
	private:
		void _initGPIO();
	public:
		Proto();
		Command getCommand(unsigned char value);
		Command read();
		
		
};


#endif

