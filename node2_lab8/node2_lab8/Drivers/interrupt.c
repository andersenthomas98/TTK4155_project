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
#include "motor.h"

#define JOYSTICK_DIR_ID 0x1
#define JOYSTICK_POS_ID 0x2
#define JOYSTICK_SLIDER_BUTTON_ID 0x3
#define START_GAME 0x4

volatile int ADC_INTERRUPT_READY = 0;
volatile uint8_t SLIDER_POS;
volatile int GAME_START = 0;
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
	//printf("can interrupt");
	if (MCP_read(MCP_CANINTF) & MCP_TX0IF) {
		//printf("Message sendt succesfully\n\r");
		
		// Reset transmit flag
		MCP_bitModify(MCP_CANINTF, MCP_TX0IF, 0);
	}
	// Message received at receive buffer 0	
	if (MCP_read(MCP_CANINTF) & MCP_RX0IF) {
		struct CAN_message msg = CAN_message_recieve();
		//printf("Message recieved with ID: %#X\n\r", msg.id);
		if (msg.id == JOYSTICK_DIR_ID) {
			printf("JOYSTICK: %d\n\r", msg.data[0]);
		}
		else if (msg.id == JOYSTICK_POS_ID){
			//printf("Joystick x pos = %d\n\r", msg.data[0]);
			//PWM_set_duty_cycle(msg.data[0]);
			//sei();
			if (msg.data[0] > 50) {
				MOTOR_set((msg.data[0]-50)*5, 0);
			} else {
				MOTOR_set(255-(5*msg.data[0]), 1);
			}
		}
		else if (msg.id == JOYSTICK_SLIDER_BUTTON_ID) {
			
			SLIDER_POS = (int8_t)msg.data[0]; // Position of (right) slider
			PWM_set_duty_cycle(msg.data[1]);  // Set servo position
			if (msg.data[2] == 2) { // If button is pressed
				//printf("Trigger!\n\r");
				PORTL &= ~(1 << PL6);  // Trigger solenoid
			}
			else {
				PORTL |= (1 << PL6);
			}
			
		}
		else if (msg.id == START_GAME){
			GAME_START = 1;
		}
		else {
			printf("CANNOT IDENTIFY MESSAGE");
		}
	
		// Reset recieve flag
		MCP_bitModify(MCP_CANINTF, MCP_RX0IF, 0);
	}
	
	if (MCP_read(MCP_CANINTF) & MCP_MERRF) {
		printf("CBE!");
		// Reset error flag
		MCP_bitModify(MCP_CANINTF, MCP_MERRF, 0);
	} 
}

