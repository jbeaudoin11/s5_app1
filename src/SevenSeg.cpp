#include "SevenSeg.h"

SevenSeg::SevenSeg(SegMode mode) {
	
	_mode = mode;
	
	for(int i=0; i<6; i++) {
		_dots[i] = 0;
	}
	for(int i=0; i<4; i++) {
		_digits[i] = 0;
	}
	
	_seg_cs =  new DigitalOut(p14);
	
	if(_mode == SPI_MODE) {
		_initSpi();
	} else {
		_initUart();
	}
}

// ========= Utilities =========

int SevenSeg::_byteArrayToInt(int b[], int length) {
    int res = 0;
	
	for(int i=0; i<length; i++) {
		if(b[i]) {
			res += 1 << i; 
		}
	}
	
	return res;
}


void SevenSeg::_splitIntIn4DigitArray(int num, char arr[4]) {
	
	char a, b, c, d, r;
	
	if(num <= -100) {
		a = '-';
	} else {
		a = '0';
	}
	
	// 1000
	r = abs(num) % 1000;
	
	// 100
	if(num > -100 && num <= -10) {
		b = '-';
	} else {
		b = (char)(r / 100);	
	}
	r %= 100;
	
	// 10
	if(num > -10 && num <= -1) {
		c = '-';
	} else {
		c = (char)(r / 10);	
	}
	
	// 1
	d = (char)(r % 10);
	
	// Offset for ascii value
	if(b != '-') {
		b += '0';	
	}
	if(c != '-') {
		c += '0';	
	}
	d += '0';
	
//	printf("%d -- %c%c%c%c\n", num, a, b, c, d);
	
	arr[0] = a;
	arr[1] = b;
	arr[2] = c;
	arr[3] = d;
}

// ========= API =========

void SevenSeg::write(int num) {
	_splitIntIn4DigitArray(num, _digits);
	
	for(int i=0; i<4; i++) {
		write(_digits[i], i);
	}
}
void SevenSeg::write(char val, int index) {
	if(_mode == SPI_MODE) {
		_writeSpi(val, index);
	} else {
		_writeUart(val, index);
	}
}
void SevenSeg::dot(int state, int index) {
	if(_mode == SPI_MODE) {
		_dotSpi(state, index);
	} else {
		_dotUart(state, index);
	}
}
void SevenSeg::clear() {
	if(_mode == SPI_MODE) {
		_clearSpi();
	} else {
		_clearUart();
	}
}

// ========= SPI =========
void SevenSeg::_initSpi() {
	_seg_spi = new SPI(p11, p12, p13);
	
	// CS on
	*_seg_cs =  0;
	
	// Settings
	_seg_spi->format(8);
	_seg_spi->frequency(100000);
	
	// Wait for setup
	wait_us(5);
	
	*_seg_cs =  1;
}

void SevenSeg::_writeSpi(char val, int index) {
	// Start writing
	*_seg_cs =  0;
	
	//_seg_spi->write(0x7B + index); // Not sure why but doesn't work properly
	
	_seg_spi->write(0x79);
	_seg_spi->write(index);
	_seg_spi->write(val);
	
	wait_us(5);
	*_seg_cs =  1;
}

void SevenSeg::_dotSpi(int state, int index) {
	_dots[index] = state;
	
	// Start writing
	*_seg_cs =  0;
	
	_seg_spi->write(0x77);
	_seg_spi->write(_byteArrayToInt(_dots, 6));
	
	wait_us(5);
	*_seg_cs =  1;
}

void SevenSeg::_clearSpi() {
	// Start writing
	*_seg_cs =  0;
	
	_seg_spi->write(0x76);
	
	wait_us(5);
	*_seg_cs =  1;
}


// ========= UART =========

void SevenSeg::_initUart() {
	
}

void SevenSeg::_writeUart(char val, int index) {
	
}

void SevenSeg::_dotUart(int state, int index) {
	
}

void SevenSeg::_clearUart() {
	
}
