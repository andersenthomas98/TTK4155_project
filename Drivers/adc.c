/*
 * adc.c
 *
 * Created: 11.09.2019 14:58:23
 *  Author: thoander
 */ 

#include "interrupt.h"
#include "adc.h"
#include "xmem.h"
#include <avr/interrupt.h>



uint8_t ADC_read_x(void) {
	// Setup to read from channel 1
	XMEM_write(0b0100, 0b010000000100);
	while (!ADC_INTERRUPT_READY) {
		// wait for interrupt from ADC
		//printf("waiting for interrupt\n\r");
	}
	ADC_INTERRUPT_READY = 0;
	uint8_t x = XMEM_read(0b010000000000);
	//printf("read_x = %d \n\r", x);
	return x;
}

uint8_t ADC_read_y(void) {
	// Setup to read from channel 2
	XMEM_write(0b0101, 0b010000000101);
	while (!ADC_INTERRUPT_READY) {
		// wait for interrupt from ADC
	}
	ADC_INTERRUPT_READY = 0;
	uint8_t y = XMEM_read(0b010000000000);
	//printf("read_y = %d \n\r", y);
	return y;
}

uint8_t ADC_slider_left(void) {
	// Setup to read from channel 2
	XMEM_write(0b0110, 0b010000000110);
	while (!ADC_INTERRUPT_READY) {
		// wait for interrupt from ADC
	}
	ADC_INTERRUPT_READY = 0;
	return XMEM_read(0b010000000000);
}

uint8_t ADC_slider_right(void) {
	// Setup to read from channel 2
	XMEM_write(0b0111, 0b010000000111);
	while (!ADC_INTERRUPT_READY) {
		// wait for interrupt from ADC
	}
	ADC_INTERRUPT_READY = 0;
	return XMEM_read(0b010000000000);
}





/*

// TODO
void ADC_calibrate(void) {
	
	
}
*/