#include "mbed.h"

// 7 Seg
SPI spi(p11, p12, p13); 
DigitalOut seg_cs(p14);

int main() {
	
	printf("Start");
	printf("\n");
	
	seg_cs = 1;
	
	spi.format(8);
	spi.frequency(9600);
	
	wait(0.1);
	
	// Start write 7seg
	seg_cs = 0;
	
	spi.write(0x76);
	spi.write('E');
	spi.write('R');
	spi.write('R');
	
	wait(0.1);
	// Stop write 7seg
  seg_cs = 1;
	
	printf("Done\n");
	
	while(1) {
		wait(0.5);
	}
	
}
