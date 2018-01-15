
#include "Test.h"


void testSevenSegSpi() {
	SevenSeg seg(SPI_MODE);
	_testSevenSeg(seg);
}

void testSevenSegUart() {
	SevenSeg seg(UART_MODE);
	_testSevenSeg(seg);
}

void _testSevenSeg(SevenSeg seg) {
	seg.clear();
	
	int index = 0;
	while(1) {
		
		seg.write('A' + (index % 4), 0);
		seg.write('A' + ((index + 1) % 4), 1);
		seg.write('A' + ((index + 2) % 4), 2);
		seg.write('A' + ((index + 3) % 4), 3);
		
		seg.dot(index % 2, 0);
		seg.dot(!(index % 2), 1);
		seg.dot(index % 2, 2);
		seg.dot(!(index % 2), 3);
		seg.dot(index % 2, 4);
		seg.dot(!(index % 2), 5);
		
		index = (index + 1) % 4;
		
		wait(0.5);
	}
}

void testAccel() {
	Accel acc(0x1D);
	
	while(1) {
		acc.update();
		
		printf("A %0.2f -- X %0.2f -- Y %0.2f -- Z %0.2f\n",
			acc.a(),
			acc.x(),
			acc.y(),
			acc.z()
		);
		
		wait(0.3);
	}
}

