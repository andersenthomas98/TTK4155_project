/*
 * lab2.c
 *
 * Created: 04.09.2019 09:57:38
 *  Author: thoander
 */ 

#include "Drivers/uart.h"
#include "Drivers/xmem.h"
#define F_CPU 4915200UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#define MYUBRR 31



int main(void)
{
	
	UART_init(MYUBRR);
	/*
		Read og write signaler til SRAM fra atmega går kun opp til litt over 1V når de egentlig skulle vært 5V.
		(Noe galt med selve atmegaen??)
	*/
	/*
	printf("Starting...\n\r");
	DDRD |= (1 << PD7);
	while (1) {
		PORTD = (1 << PD7);
		_delay_ms(500);
		PORTD = (0 << PD7);
		_delay_ms(500);
	}*/
	
	XMEM_init();
	SRAM_test();
	
	return 0;
	
}