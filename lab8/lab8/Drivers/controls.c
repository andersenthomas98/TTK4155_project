/*
 * controls.c
 *
 * Created: 12.09.2019 16:08:09
 *  Author: thoander
 */ 

#include "controls.h"
#include "adc.h"
#include "can.h"
#include <avr/io.h>


pos_t joystick_pos(void) {
	int8_t x_pos = (ADC_read_x()*100/128)-100;
	int8_t y_pos = (ADC_read_y()*100/128)-100;
	pos_t pos = {x_pos, y_pos};
	return pos;
}

dir_t joystick_dir(void) {
	pos_t pos = joystick_pos();
	if (pos.x <= -10 && pos.x*pos.x > pos.y*pos.y){
		return LEFT;
	}
	else if (pos.x >= 10 && pos.x*pos.x > pos.y*pos.y){
		return RIGHT;
	}
	else if (pos.y <= -10 && pos.x*pos.x < pos.y*pos.y){
		return DOWN;
	}
	else if (pos.y >= 10 && pos.x*pos.x < pos.y*pos.y){
		return UP;
	}
	return NEUTRAL;
}
/*
void continuous_send(){
	timer 2 = 0
	send joystick pos 
	send slider pos
	send button state
	while timer 2 count < 100 {
		
	}
}*/

void send_joystick_dir(void) {
	msg_t msg;
	msg.id = 0x01;
	msg.length = 1;
	msg_ptr msgPtr = &msg;
	uint8_t joystickDirection = joystick_dir();
	msg.data[0] = joystickDirection;
	CAN_message_send(msgPtr);
}

void send_joystick_pos(void) {
	msg_t msg;
	msg.id = 0x02;
	msg.length = 2;
	msg_ptr msgPtr = &msg;
	pos_t pos = joystick_pos();
	uint8_t stdPosX = ((pos.x + 101) / 4) * 2; // Senker oppløsning for å unngå dirring ved å bruke heltalldivisjon
	uint8_t stdPosY = ((pos.y + 101) / 4) * 2;
	msg.data[0] = stdPosX;
	msg.data[1] = stdPosY;
	CAN_message_send(msgPtr);
}

void btn_init(void) {
	DDRB &= ~(1 << PB0);
	DDRB &= ~(1 << PB1);
}

int btn_left(void) {
	return (PINB & (1<<PB0));
}

int btn_right(void) {
	return (PINB & (1<<PB1));
}