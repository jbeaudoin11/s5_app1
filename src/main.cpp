#include "mbed.h"
#include "SevenSeg.h"
#include "Accel.h"
#include "Test.cpp"

enum AppMode {
	MAIN_SPI,		// Main with 7seg in SPI mode
	MAIN_UART,		// Main with 7seg in UART mode
	MAIN_PROTO,		// Main custom protocol
	
	TEST_SEG_SPI,	// Test 7seg in SPI mode
	TEST_SEG_UART,	// Test 7seg in UART mode
	TEST_ACC,		// Test acc, serial to pc
	
	TEST_CMD_VALID		// Test custom protocol cmd validation
};

// To change 
//AppMode APP_MODE = MAIN_SPI;
//AppMode APP_MODE = MAIN_UART;
AppMode APP_MODE = MAIN_PROTO;

//AppMode APP_MODE = TEST_SEG_SPI;
//AppMode APP_MODE = TEST_SEG_UART;
//AppMode APP_MODE = TEST_ACC;
//AppMode APP_MODE = TEST_CMD_VALID;

int main() {
	printf("--------\n");
//	
//	printf("#define LPC_GPIO2_FIOPIN (int *) 0x%0.2X\n",&(LPC_GPIO2->FIOPIN));
//	printf("#define LPC_GPIO2_FIODIR (int *) 0x%0.2X\n",&(LPC_GPIO2->FIODIR));
//	printf("#define LPC_PINCON_PINSEL4 (int *) 0x%0.2X\n",&(LPC_PINCON->PINSEL4));
//	printf("#define LPC_PINCON_PINMODE4 (int *) 0x%0.2X\n",&(LPC_PINCON->PINMODE4));
//	
	switch(APP_MODE) {
		case MAIN_SPI: {
			Accel acc(0x1D);
			SevenSeg seg(SPI_MODE);
	
			seg.clear();
		
			while(1) {
				acc.update();
				
				seg.write((int) acc.a());
				
				wait(0.3);
			}
		}
		
		case MAIN_UART: {
			Accel acc(0x1D);
			SevenSeg seg(UART_MODE);
			
			seg.clear();
	
			while(1) {
				acc.update();
				
				seg.write((int) acc.a());
				
				wait(0.3);
			}
		}		
		
		case MAIN_PROTO: {
			Proto proto;
			SevenSeg seg(UART_MODE);
			
			seg.clear();
	
			while(1) {
//		switch(proto.read()) {
//			
//			
//			
//		}
				printf("%d\n", proto.read());
				
//				seg.write((int) acc.a());
			}
		}
		
		case TEST_SEG_SPI:
			testSevenSegSpi();
		break;
		
		case TEST_SEG_UART:
			testSevenSegUart();
		break;
		
		case TEST_ACC:
			testAccel();
		break;
		
		case TEST_CMD_VALID:
			testCommand();
		break;
	}
	
	return 0;
}




