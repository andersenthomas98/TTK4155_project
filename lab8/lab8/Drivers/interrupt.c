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


void INTERRUPT_init() {
	// disable global interrupts (set SREG register)
	cli();
	
	// Enable that a falling edge generates an interrupt request for INT0
	MCUCR |= (1 << ISC01);
	MCUCR &= ~(1 << ISC00);
	
	
	// Enable that a falling edge generates an interrupt request for INT1
	MCUCR |= (1 << ISC11);
	MCUCR &= ~(1 << ISC10);	

	
	// Enable interrupt on INT0 (from ADC) and INT1 (from MCP)
	GICR |= (1 << INT0);
	GICR |= (1 << INT1); 
		
	// Setup for timer interrupt
	OCR0 = 100;
	//TIMSK |= (1 << OCIE0);	OBS RENABLE DENNE
		
		
	// Enable global interrupts (set SREG register)
	sei();
}

// Interrupt for ADC
ISR(INT0_vect) {
	// Disable global interrupts while executing an ISR (?)
	//cli();
	ADC_INTERRUPT_READY = 1;
	
	// Reset interrupt flag
	//GIFR &= ~(1 << INTF0);
	//GIFR |= (1 << INTF0);
	//printf("routine finished\n\r");
	//sei();
}

// CAN interrupts
ISR(INT1_vect) {
	if (MCP_read(MCP_CANINTF) & MCP_TX0IF) {
		//printf("Message sendt succesfully\n\r");
		
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
	
		// Reset receive flag
		MCP_bitModify(MCP_CANINTF, MCP_RX0IF, 0);
	}
	if (MCP_read(MCP_CANINTF) & MCP_MERRF) {
		printf("CAN BUS ERROR!");
		MCP_bitModify(MCP_CANINTF, MCP_MERRF, 0);
	}
}

ISR(TIMER0_COMP_vect) {
	sei();

	send_joystick_pos();
	// Timer is reset automatically
}