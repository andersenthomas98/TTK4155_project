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

void timer_0division1024Init(void) {

	// start the timer
	TCCR0 = 0b00100101;
	// set prescaler to 1024 (101) and start the timer


}

void timer_2division1024Init(void) {

	// start the timer
	TCCR2 = 0b00100101;
	// set prescaler to 1024 (101) and start the timer


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

void TIM8_WriteTCNT2(uint8_t i)
{
	unsigned char sreg;
	//uint8_t i;
	/* Save Global Interrupt Flag */
	sreg = SREG;
	/* Disable interrupts */
	cli();
	/* Set TCNTn to i */
	TCNT2 = i;
	/* Restore Global Interrupt Flag */
	SREG = sreg;
	sei();
}

unsigned int TIM8_ReadTCNT2(void)
{
	unsigned char sreg;
	uint8_t i;
	/* Save Global Interrupt Flag */
	sreg = SREG;
	/* Disable interrupts */
	cli();
	/* Read TCNTn into i */
	i = TCNT2;
	/* Restore Global Interrupt Flag */
	SREG = sreg;
	sei();
	return i;
}