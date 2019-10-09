/*
 * interrupt.c
 *
 * Created: 11.09.2019 14:14:53
 *  Author: thoander
 */ 
#include <avr/interrupt.h>
#include "interrupt.h"
#include "can.h"
#include "mcp2515.h"
#include "uart.h"

volatile int ADC_INTERRUPT_READY = 0;
//volatile int SPI_TRANSMISSION_COMPLETE = 0;

void INTERRUPT_init() {
	// disable global interrupts (set SREG register)
	cli();
	
	// The falling edge of INT2 generates an interrupt request
	EICRA &= ~(1 << ISC20);
	EICRA |= (1 << ISC21); 
	
	// Enable interrupt on INT2
	EIMSK |= (1 << INT2);
		
	// Enable global interrupts (set SREG register)
	sei();
}


// CAN interrupts
ISR(INT2_vect) {
	printf("interrupt\n\r");
	if (MCP_read(MCP_CANINTF) & MCP_TX0IF) {
		printf("Message sendt succesfully\n\r");
		
		// Reset transmit flag
		MCP_bitModify(MCP_CANINTF, MCP_TX0IF, 0);
	}
	// Message recieved at recieve buffer 0
	if (MCP_read(MCP_CANINTF) & MCP_RX0IF) {
		struct CAN_message msg = CAN_message_recieve();
		printf("--- Message recieved ---\n\r");
		printf("ID: %#X \n\r", msg.id);
		printf("Length: %d \n\r", msg.length);
		printf("Data[0] = %#X \n\r", msg.data[0]);
	
		// Reset recieve flag
		MCP_bitModify(MCP_CANINTF, MCP_RX0IF, 0);
	}
	if (MCP_read(MCP_CANINTF) & MCP_MERRF) {
		printf("CAN BUS ERROR!");
	}
}




