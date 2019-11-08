/*
 * timer.c
 *
 * Created: 06.11.2019 13:24:35
 *  Author: axeltb
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

void timer_0division1024Init(void) {

	// start the timer
	TCCR0B = 0b00000101; //normal mode, prescalar 1024
	// set prescaler to 1024 (111) and start the timer


}
/*
void timer_3division256Init(){
	TCCR3B = 0b00000100;	//set prescalar to 256 (0b100)
	TIMSK3 = 0b00000001;	//enable TOIE3, overflow interrupt
}
*/
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
