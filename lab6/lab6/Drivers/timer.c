/*
 * timer.c
 *
 * Created: 02.10.2019 12:42:42
 *  Author: thoander
 */ 

#include "timer.h"
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#define F_CPU 4915200

void timer_8bit256divisionCheckOnlyinit(void) {

	// start the timer
	TCCR0 = 0b00000101;
	// set prescaler to 256 and start the timer
	TIMSK &= ~(1 << OCIE0 | 1 << TOIE0);
	// disable both compare and overflow interrupts

}

void TIM8_WriteTCNT0(uint8_t i)
{
	unsigned char sreg;
	//uint8_t i;
	/* Save Global Interrupt Flag */
	sreg = SREG;
	/* Disable interrupts */
	cli();
	/* Set TCNTn to i */
	TCNT0 = i;
	/* Restore Global Interrupt Flag */
	SREG = sreg;
	sei();
}

unsigned int TIM8_ReadTCNT0(void)
{
	unsigned char sreg;
	uint8_t i;
	/* Save Global Interrupt Flag */
	sreg = SREG;
	/* Disable interrupts */
	cli();
	/* Read TCNTn into i */
	i = TCNT0;
	/* Restore Global Interrupt Flag */
	SREG = sreg;
	sei();
	return i;
}