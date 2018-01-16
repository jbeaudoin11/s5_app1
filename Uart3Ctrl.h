#ifndef UART_3_CTRL_H
#define UART_3_CTRL_H

#include <cstdio>

#define LSR_THRE_EMPTY (0x1 << 5)
#define LPC_SC_PCONP (int *) 0x400FC0C4
#define LPC_SC_PCLKSEL1 (int *) 0x400FC1AC
#define LPC_PINCON_PINSEL0 (int *) 0x4002C000
#define LPC_UART3_LCR (int *) 0x4009C00C
#define LPC_UART3_DLM (int *) 0x4009C004
#define LPC_UART3_DLL (int *) 0x4009C000
#define LPC_UART3_FCR (int *) 0x4009C008
#define LPC_UART3_LSR (int *) 0x4009C014
#define LPC_UART3_THR (int *) 0x4009C000

using namespace std;

class Uart3Ctrl {
	
	private:

		void _initUart3();
	
	public:
	
		Uart3Ctrl();
		
		void write(char val);
	
};
	
#endif
