#include "mbed.h"
#include "SevenSeg.h"
#include "Accel.h"

int main() {
	printf("Start\n");
	
	SevenSeg seg(SPI_MODE);
	seg.clear();
	
	Accel acc(0x1D);
	
	while(1) {
		acc.update();
		
		seg.write((int) acc.a());
		
		wait(0.3);
	}

	
//	
//	seg.write('A', 0);
//	seg.write('B', 1);
//	seg.write('C', 2);
//	seg.write('D', 3);
//	
//	seg.dot(1, 0);
//	seg.dot(1, 1);
////	seg.dot(1, 2);
//	seg.dot(1, 3);
////	seg.dot(1, 4);
//	seg.dot(1, 5);
//	
	printf("Done\n");
	
//	while(1) {
//		wait(10);
//	}
	
	return 0;
}


