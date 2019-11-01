/*
 * dac.c
 *
 * Created: 30.10.2019 12:41:05
 *  Author: annemmat
 */ 

#include "motor.h"
#include "TWI_Master.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <avr/delay.h>

#define _OE PH5
#define SEL PH3
#define DIR PH1
#define _RST PH6
#define EN PH4
#define DO0 PK0
#define DO1 PK1
#define DO2 PK2
#define DO3 PK3
#define DO4 PK4
#define DO5 PK5
#define DO6 PK6
#define DO7 PK7

void MOTOR_init(void) {
	TWI_Master_Initialise();
	
	// Initialize output pins for input to motorbox
	DDRH |= (1 << EN) | (1 << DIR) | (1 << _RST) | (1 << SEL) | (1 << _OE);
	
	// Initialize input pins for output from motorbox (encoder value)
	DDRK &= ~(1 << DO0) | ~(1 << DO1) | ~(1 << DO2) | ~(1 << DO3) | ~(1 << DO4) | ~(1 << DO5) | ~(1 << DO6) | ~(1 << DO7);
	
	// Reset encoder value
	PORTH &= ~(1 << _RST);
	_delay_us(130);
}

void MOTOR_DAC_write(uint8_t d) {
	// Send address byte, which DAC to use and data
						   /*Address    DAC0    data  */
	unsigned char msg[3] =  {0b01010000, 0b0, d};	
	TWI_Start_Transceiver_With_Data(&msg, 3);
}

void MOTOR_set(uint8_t speed, int dir) {
	// Enable motor
	PORTH |= (1 << PH4);
	
	// Set speed of motor
	MOTOR_DAC_write(speed);
	
	// Set direction of motor
	if (dir == 1) {
		PORTH |= (1 << DIR);
	}
	else {
		PORTH &= ~(1 << DIR);
	}
}


int16_t MOTOR_encoder_read(void) {
	
	PORTH |= (1 << _RST);
	
	// Enable output of encoder
	PORTH &= ~(1 << _OE);
	
	// Get low byte
	PORTH &= ~(1 << SEL);
	
	_delay_us(120);
	
	// Read low byte
	uint16_t LSB = PINK;
	printf("LSB = %d\n\r", LSB);
	
	// Get LOW byte
	PORTH |= (1 << SEL);
	
	_delay_us(20);
	
	// Read high byte
	uint16_t MSB = PINK;
	printf("MSB = %d\n\r", MSB);
	
	// Disable output of encoder
	PORTH |= (1 << _OE);
	
	int16_t encoder_value = (MSB << 8) + LSB;
	
	printf("encoder value = %d\n\r", encoder_value);
	
	return encoder_value;
}