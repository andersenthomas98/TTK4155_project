/*
 * internalADC.c
 *
 * Created: 23.10.2019 14:27:44
 *  Author: thoander
 */ 

#include <avr/io.h>

void IR_init(void) {
	// Initialization of the internal ACD of the atmega2560 (convert analog signals [0, 2.56]V to digital signals [0-255]) 
	
	// Set PF0 (ADC0) as input
	DDRF &= ~(1 << PF0);
	
	// Set internal 2.56 voltage reference, set ADC0 as input (MUX5 = 0, MUX4:0 = 0), and left adjust the result of the conversion in the ADCH register
	ADMUX |= (1 << REFS1) | (1 << REFS0) | (1 << ADLAR);
	
	// Set ADC prescaler to a division factor of 32 (0.026 ms for each new sample), enable ADC auto trigger (free running mode set by default)
	ADCSRA |= (1 << ADPS2) | (1 << ADPS0) | (1 << ADATE);
	
	// Enable the ADC
	ADCSRA |= (1 << ADEN) | (1 << ADSC);
}

uint8_t IR_read(void) {
	// For 8-bit resolution, we only need to read ADCH and not ADCL
	return ADCH;
	// TODO: Return the average value of the digital signal over 4 A-D conversions (digital filter to reduce noise) --> maybe not needed
}

// TODO: create a function that is able to count the score. This will later be used for the game application.