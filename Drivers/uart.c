#define F_CPU 4915200
#define BAUD 9600
/*For some reason using MYUBRR like this, does not work... */
//#define MYUBRR ( (F_CPU) / (BAUD*16UL)) - 1
#define MYUBRR 31
#include <avr/io.h>
#include <stdio.h>
#include<util/delay.h>
#include "uart.h"

void UART_transmit(unsigned char data) {
	// Wait for empty transmit buffer
	while ( ! (UCSR0A & (1<<UDRE0))) {
		// waiting...
	}
	// Put data into buffer, sends the data
	UDR0 = data;
}

unsigned char UART_receive(void) {
	// Wait for data to be received
	while(!(UCSR0A & (1 << RXC0))) {
		// wait...
	}
	return UDR0;
	
}

void UART_init(unsigned int ubrr) {
	// Set baud rate
	UBRR0H = ubrr>>8;
	UBRR0L = ubrr;
	
	// Enable receiver and transmitter
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	
	// Set frame format: 8data, 2stop bit
	UCSR0C = (1<<URSEL0) | (1<<USBS0) | (3<<UCSZ00);
	
	fdevopen(UART_transmit, UART_receive);
}