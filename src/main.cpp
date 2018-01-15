#include "mbed.h"
#include "SevenSeg.h"
#include "Accel.h"
#include "Test.cpp"

enum AppMode {
	MAIN_SPI,		// Main with 7seg in SPI mode
	MAIN_UART,		// Main with 7seg in UART mode
	
	TEST_SEG_SPI,	// Test 7seg in SPI mode
	TEST_SEG_UART,	// Test 7seg in UART mode
	TEST_ACC		// Test acc, serial to pc
};

// To change 
//AppMode APP_MODE = MAIN_SPI;
//AppMode APP_MODE = MAIN_UART;

//AppMode APP_MODE = TEST_SEG_SPI;
//AppMode APP_MODE = TEST_SEG_UART;
AppMode APP_MODE = TEST_ACC;

int main() {
	printf("--------\n");
	
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
		
		case TEST_SEG_SPI:
			testSevenSegSpi();
		break;
		
		case TEST_SEG_UART:
			testSevenSegUart();
		break;
		
		case TEST_ACC:
			testAccel();
		break;
	}
	
	return 0;
}




