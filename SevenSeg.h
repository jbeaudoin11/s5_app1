#ifndef SEVEN_SEG
#define SEVEN_SEG

#include <cmath>

#include "mbed.h"

enum SegMode {
	SPI_MODE,
	UART_MODE
};

class SevenSeg {
	private:
		SegMode _mode;
		int _dots[6];
		char _digits[4];
		
		SPI *_seg_spi;
		DigitalOut *_seg_cs;
		
		int _byteArrayToInt(int b[], int length);
		void _splitIntIn4DigitArray(int num, char arr[4]);
		
		void _initSpi();
		void _writeSpi(char val, int index);
		void _dotSpi(int state, int index);
		void _clearSpi();
		
	
		void _initUart();
		void _writeUart(char val, int index);
		void _dotUart(int state, int index);
		void _clearUart();
		
	public:
		SevenSeg(SegMode mode);
	
		void write(int num);
		void write(char val, int index);
		void dot(int state, int index);
		void clear();
	
};




#endif
