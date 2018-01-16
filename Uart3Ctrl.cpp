
#include "Uart3Ctrl.h"

Uart3Ctrl::Uart3Ctrl() {
	_initUart3();
}

void Uart3Ctrl::_initUart3() {

	// Power up the UART3 it's disabled on powerup.
	*(LPC_SC_PCONP)       |= (0x1 << 25);

	// Setup the PCLK for UART3
	*(LPC_SC_PCLKSEL1)    &= ~(0x3 << 18); // Reset PCLK
	*(LPC_SC_PCLKSEL1)    |=  (0x1 << 18); // Set PCLK = CCLK

	// Setup pin 9 (P0.0) & 10 (P0.1) in UART mode
	*(LPC_PINCON_PINSEL0) &= ~0x3;	// Reset
	*(LPC_PINCON_PINSEL0) |= 0xA;		// 

	// 9600 Baud
	*(LPC_UART3_LCR)       = (0x1 << 7);	// Enable DLM & DLL edit
	*(LPC_UART3_DLM)       = 0x2; 		// MSB
	*(LPC_UART3_DLL)       = 0x71;		// LSB
	*(LPC_UART3_LCR)       = 0x3;			// Set for 8 bit per transaction

	// Enable and reset UART3 FIFOs (RX + TX).
	*(LPC_UART3_FCR)       = 0x7;
}

void Uart3Ctrl::write(char val) {
	
	// Wait for the THR register to be writable
	while((*(LPC_UART3_LSR) & LSR_THRE_EMPTY) == 0x0) {
		// TODO wait_us(..) ?
	}

	// Write the value so it gets add to the FIFO
	*(LPC_UART3_THR) = val;

}
