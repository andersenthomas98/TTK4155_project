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
	int8_t x_pos = (ADC_read_x()*100/131)-100;
	int8_t y_pos = (ADC_read_y()*100/131)-100;
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

void send_joystick_dir(void) {
	msg_t msg;
	msg.id = 0x01;
	msg.length = 1;
	msg_ptr msgPtr = &msg;
	uint8_t joystickDirection = joystick_dir();
	msg.data[0] = joystickDirection;
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