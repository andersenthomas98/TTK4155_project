/*
 * lab2.c
 *
 * Created: 04.09.2019 09:57:38
 *  Author: thoander
 */ 

#include "Drivers/uart.h"
#include "Drivers/xmem.h"
#include "Drivers/interrupt.h"
#include "Drivers/adc.h"
#define F_CPU 4915200UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#define MYUBRR 31


int main(void)
{
	UART_init(MYUBRR);
	XMEM_init();
	INTERRUPT_init();
	printf("Starting....\n\r");
	
	while(1) {
		//printf("Interrupt ready: %d", ADC_INTERRUPT_READY);
		int x = ADC_read_x();
		int y = ADC_read_y();
		printf("x = %d \n\r y = %d \n\r", x, y);
		
		_delay_ms(500);
	}
	
	return 0;
	
}