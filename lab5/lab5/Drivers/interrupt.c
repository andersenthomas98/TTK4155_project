/*
 * interrupt.c
 *
 * Created: 11.09.2019 14:14:53
 *  Author: thoander
 */ 
#include <avr/interrupt.h>
#include "interrupt.h"

volatile int ADC_INTERRUPT_READY = 0;
//volatile int SPI_TRANSMISSION_COMPLETE = 0;

void INTERRUPT_init() {
	// Enable global interrupts (set SREG register)
	sei();
	
	// Enable that a falling edge generates an interrupt request for INT0
	MCUCR |= (1 << ISC01);
	MCUCR &= ~(1 << ISC00);
	
	/*
	// Enable that a rising  edge generates an interrupt request for INT1
	MCUCR |= (1 << ISC11);
	MCUCR |= (1 << ISC10);	
	*/
	
	// Enable interrupt on INT0 (ADC) and INT1 (MCU)
	GICR |= (1 << INT0);
	GICR |= (1 << INT1); 
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

/*
ISR(INT1_vect) {
	SPI_TRANSMISSION_COMPLETE = 1;
	
	// SPIF (SPI Interrupt Flag) is cleared by hardware when executing this interrupt handling vector.
}
*/


