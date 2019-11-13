/*
 * controls.h
 *
 * Created: 12.09.2019 16:08:26
 *  Author: thoander
 */ 


#ifndef CONTROLS_H_
#define CONTROLS_H_

#include <stdint.h>

typedef struct {
	int8_t x;
	int8_t y;
} pos_t;

typedef enum {
	LEFT, RIGHT, UP, DOWN, NEUTRAL
} dir_t;

pos_t joystick_pos(void);

dir_t joystick_dir(void);

void send_joystick_dir(void);

void send_joystick_pos(void);

void send_slider_joystick_button(uint8_t currentSliderValue, int currentJoystickValue, int currentButtonValue);

void btn_init(void);

int btn_right(void);

int btn_left(void);


#endif /* CONTROLS_H_ */