/*
 * HelloWorld.c
 *
 * Created: 29.08.2019 15:33:07
 *  Author: thoander
 */ 

#define MYUBRR 31
#include <avr/io.h>
#include "Drivers/uart.h"

int main(void)
{
	UART_init(MYUBRR);
	while(1) {
		printf("Hei!");
		_delay_ms(500);
	}
	
}