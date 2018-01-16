#include "Proto.h"

Proto::Proto(){
	_initGPIO();
}

void Proto::_initGPIO(){
	*(LPC_PINCON_PINSEL4) &= ~(3<<11);
	*(LPC_PINCON_PINSEL4) &= ~(3<<9);
	*(LPC_GPIO2_FIODIR) |= (1<<5);
	*(LPC_GPIO2_FIODIR) |= (1<<4);
	*(LPC_PINCON_PINMODE4) |= (3<<10);
	*(LPC_PINCON_PINMODE4) |= (3<<8);
	
}

Command Proto::read(){
	char counter=0;
	char done = 0;
//	int value;
	unsigned char result = 0;
	
	unsigned char clk = 0;
	unsigned char value = 0;

	DigitalIn _clk(p22);
	DigitalIn _value(p21);
	
	while(counter < 7)
	{
		clk = (unsigned char) _clk;
		
		//clk = !!(*(LPC_GPIO2_FIOPIN) & (1 << 4)); // Clock is 0 or 1
		//value = !!(*(LPC_GPIO2_FIOPIN) & (1 << 5)); // Bit is 0 or 1
		
		//printf("Clk: %d\n", (int)clk);
		//printf("Data: %d\n", value);
	
		// If we did not already read the value and clk == 1
		if(clk && !done){
			//value = !!(*(LPC_GPIO2_FIOPIN) & (1 << 5)); // Bit is 0 or 1
			
			value = (unsigned char) _value;
			if(value) {
				result |= (1 << (6 - counter));
			}
		
			done = 1;
			counter++;
		}
		else if(!clk){
			done=0;
		}
		wait_us(10);
	}
	
	//printf("0x%.2X\n", result);
	
	return getCommand(result);
}

Command Proto::getCommand(unsigned char value){
	unsigned char temp;
	int counter = 0;
	
	// Start bit == 1
	temp = (unsigned char) (value | ~(1 << 6));
	if(temp != 0xFF ) {
		return ERROR; 
	}

	// Stop bit == 1
	temp = (unsigned char) (value | ~(1 << 0));
	if(temp != 0xFF ) {
		return ERROR; 
	}
	
	// Parity check
	for(int i=5; i>1; i--)
	{	
		temp = (unsigned char) (value | ~(1 << i));
		if(temp == 0xFF ) {
			counter++;
		}
		
	}
	
	temp = (unsigned char) (value | ~(1 << 1));
	if((temp == 0xFF)!=(counter%2)) {
		 return ERROR;
	}
	
	// Command On | Off
	char cmd = 0;	
	temp = (unsigned char) (value | ~(1 << 5));
	if(temp == 0xFF ) {
		cmd = 1;
	}
		
	// Function
	temp = (value & ~(0b11100011)) >> 2;
	switch(temp){
		case 0 :
			return cmd ? DOT1_ON:DOT1_OFF;
		case 1 :
			return cmd ? DOT2_ON:DOT2_OFF;
		case 2:
			return cmd ? DOT3_ON:DOT3_OFF;
		case 3:
			return cmd ? DOT4_ON:DOT4_OFF;
		case 4:
			return cmd ? DOT5_ON:DOT5_OFF;
		case 5:
			return cmd ? DOT6_ON:DOT6_OFF;
		case 6:
			return cmd ? LIGHT_UP:LIGHT_DOWN;
		default:
			
			printf("default\n");
			return ERROR;
	}
	
}
