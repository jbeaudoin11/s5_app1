#ifndef UART_3_CTRL_H
#define UART_3_CTRL_H

#include <cstdio>
#include "LPC17xx.h"

#define LSR_THRE_EMPTY (0x1 << 5)

using namespace std;

class Uart3Ctrl {
	
	private:

		void _initUart3();
	
	public:
	
		Uart3Ctrl();
		
		void write(char val);
	
};
	
#endif
