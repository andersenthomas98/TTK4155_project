/*
 * dac.c
 *
 * Created: 30.10.2019 12:41:05
 *  Author: annemmat
 */ 

#include "motor.h"
#include "TWI_Master.h"
#include "interrupt.h"
#include "timer.h"
#include "IR.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <avr/delay.h>
#include <stdlib.h>

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
	
	PORTH |= (1 << EN);
	PORTH |= (1 << _OE);
	PORTH |= (1 << _RST);

	// Reset encoder value
	PORTH &= ~(1 << _RST);
	_delay_us(100);
	PORTH |= (1 << _RST);
	
	// Initialize PL6 as output to trigger the solenoid
	DDRL |= (1 << PL6);
	PORTL |= (1 << PL6);
}

void MOTOR_DAC_write(uint8_t d) {
	// Send address byte, which DAC to use and data
						   /*Address    DAC0    data  */
	unsigned char msg[3] =  {0b01010000, 0b0, d};	
	TWI_Start_Transceiver_With_Data(&msg, 3);
}

// Speed = [0, 255], dir = 0 / 1
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

	// Enable output of encoder
	PORTH &= ~(1 << _OE);
	
	// Get high byte
	PORTH &= ~(1 << SEL);
	
	// Read high byte
	uint8_t LSB = PINK;
	//printf("LSB = %d\r\n", LSB);

	_delay_ms(20); // DEN MÅ VÆRE HER!!!!
	
	// Get LOW byte
	PORTH |= (1 << SEL);
	
	// Read low byte
	uint8_t MSB = PINK;
	//printf("MSB = %d, LSB = %d\r\n", MSB, LSB);
	
	// Disable output of encoder
	//PORTH |= (1 << _OE);
	
	int16_t encoder_value = (MSB << 8) | LSB;
	
	//printf("encoder value = %6d\r\n", encoder_value);
	
	return encoder_value;
}

void MOTOR_control() {
	int last_error = 0;
	float integral_error = 0;
	float Kp = 0.035;
	float Ki = 0.2;
	float K_d = 0.025;
	float T = 0.003;//0.01;

	int16_t output = 0;
	int16_t error = 0;
	int16_t value = MOTOR_encoder_read();
	int16_t lastValue = value;
	
	MOTOR_set(0, 0);
	
	printf("waiting for game start\n\r");
	while (!GAME_START); // Do nothing
	printf("game starting\n\r");

	//timer_3division256Init();	//start the score timer
	
	// Reset encoder value right after we start
	PORTH &= ~(1 << _RST);
	_delay_us(100);
	PORTH |= (1 << _RST);

	uint16_t reference = (255 - SLIDER_POS) * 35;
	//printf("reference = %6d\r", reference);
	while (1) {
		TIM8_WriteTCNT0(0);
		value = MOTOR_encoder_read();
		reference = (255 - SLIDER_POS) * 35;	
		error = reference - value;
		if (error == 0){
			integral_error = 0;
		}
		else{
			integral_error += error;
		}
		output = (Kp * error) + (T * Ki * integral_error) - (K_d * (value - lastValue));
		printf("reference=%4d,slider_pos=%3d, controller output=%4d\r", reference, SLIDER_POS, output);
		//_delay_ms(200);
		///*
		if (abs(output) == output){
			if (output > 255){
				MOTOR_set(255, 0);
			}
			else{
				MOTOR_set(output, 0);				
			}
		}
		else{
			if (output < (-255)){
				MOTOR_set(255, 1);
			}
			else{
				MOTOR_set(abs(output), 1);
			}
		}
		//*/
		//printf("IR value = %4d\r", IR_read());
		if (IR_read() < 100){
			GAME_SCORE = 0;
		}
		while(TIM8_ReadTCNT0() < 50);	//OBSOBS her 157 for å få ca T = 0.01
	}
	
}

