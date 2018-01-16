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
	printf("-------- Start --------\n");
	
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
			SevenSeg seg(SPI_MODE);
			
				seg.clear();
	
			while(1) {
				
				
				switch(proto.read()) {
					case DOT1_ON:
						seg.dot(1, 0);
					break;
					case DOT1_OFF:
						seg.dot(0, 0);
					break;
					case DOT2_ON:
						seg.dot(1, 1);
					break;
					case DOT2_OFF:
						seg.dot(0, 1);
					break;
					case DOT3_ON:
						seg.dot(1, 2);
					break;
					case DOT3_OFF:
						seg.dot(0, 2);
					break;
					case DOT4_ON:
						seg.dot(1, 3);
					break;
					case DOT4_OFF:
						seg.dot(0, 3);
					break;
					case DOT5_ON:
						seg.dot(1, 4);
					break;
					case DOT5_OFF:
						seg.dot(0, 4);
					break;
					case DOT6_ON:
						seg.dot(1, 5);
					break;
					case DOT6_OFF:
						seg.dot(0, 5);
					break;
					case LIGHT_UP:
						seg.lightUp();
					break;
					case LIGHT_DOWN:
						seg.lightDown();
					break;
					default:
//							seg.write('E', 0);
//							seg.write('r', 1);
//							seg.write('r', 2);
				}
				
//				printf("%d\n", proto.read());
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




