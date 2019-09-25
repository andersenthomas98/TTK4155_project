/*
 * menu.c
 *
 * Created: 25.09.2019 09:35:24
 *  Author: thoander
 */ 

#include "adc.h"
#include "menu.h"
#include "oled.h"
#include "controls.h"
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include <util/delay.h>

#define F_CPU 4915200

void MENU_print_children(menu_ptr item) {
	for (int i = 0; i<item->num_children; i++) {
		if (item->selectedChild == i) {
			OLED_print_string("-", i*128);
			OLED_print_string(item->children[i]->name, i*128 + 8);
		}
		else{
			OLED_print_string(item->children[i]->name, i*128);
		}
	}
}

void MENU_navigate(menu_ptr item) {
	menu_ptr currentMenu = item;
	while(1){
		if (joystick_dir() != NEUTRAL) {
			switch(joystick_dir()) {
				case DOWN:
					if (currentMenu->num_children == currentMenu->selectedChild + 1){
						currentMenu->selectedChild = 0;
					}
					else{
						currentMenu->selectedChild += 1;
					}
					break;
				case UP:
					if (currentMenu->selectedChild == 0){
						currentMenu->selectedChild = currentMenu->num_children - 1;
					}
					else{
						currentMenu->selectedChild -= 1;
					}
					break;
				case RIGHT:
					if (currentMenu->children[currentMenu->selectedChild]->num_children == 0){
						OLED_clearAll();
						currentMenu->children[currentMenu->selectedChild]->fun_ptr();
					}
					else{
						currentMenu = currentMenu->children[currentMenu->selectedChild];
					}
					break;
				case LEFT:
					if (currentMenu->parent != NULL){
						currentMenu = currentMenu->parent;
					}
					break;
			}
			while (joystick_dir() != NEUTRAL);
		}
	OLED_clearAll();
	MENU_print_children(currentMenu);
	OLED_refresh();
	}
}

void MENU_veryFunInvertingFunction(){
	OLED_clearAll();
	OLED_refresh();
	while(1){
		if (joystick_dir() == DOWN){
			XMEM_write(0xA7, 0xA7);
		}
		else{
			XMEM_write(0xA6, 0xA6);
		}
	}
}

void MENU_animation() {
	int x = 20;
	int y = 10;
	int x_vel = 3;
	int y_vel = 2;
	while (1) {
		x += x_vel;
		y += y_vel;
		if (x <= 0 || x >= 127) {
			x_vel *= -1;
		}
		if (y <= 0 || y >= 63) {
			y_vel *= -1;
		}
		OLED_set_pixel(x, y);
		OLED_refresh();
		_delay_ms(50);
	}
}


void MENU_pong() {
	float x = 63;
	float y = 31;
	float x_vel = 0.5;
	float y_vel = 0;
	float rightPaddleY = 31;
	float leftPaddleY = 31;
	float leftPaddleX = 3;
	float rightPaddleX = 124;
	int rightPoints = 0;
	int leftPoints = 0;
	float difference = 0;
	while (1) {
		float x = 63;
		float y = 31;
		x_vel = 1;
		y_vel = 0;
		while (1){
			rightPaddleY = (ADC_slider_right())/4.0;
			leftPaddleY = (ADC_slider_left())/4.0;
			x += x_vel;
			y += y_vel;
			if (x <= 0) {
				leftPoints += 1;
				break;
			}
			else if (x >= 127) {
				rightPoints += 1;
				break;
			}
			else if (x == leftPaddleX + 1 && y <= leftPaddleY + 4 && y >= leftPaddleY - 4){
				difference = y - leftPaddleY;
				y_vel = difference / 8.0;
				x_vel = 0.5;
			}
			else if (x == rightPaddleX - 1 && y <= rightPaddleY + 4 && y >= rightPaddleY - 4){
				difference = y - rightPaddleY;
				y_vel = difference / 8.0;
				x_vel = -0.5;
			}
			if (y <= 0 || y >= 63) {
				y_vel = -y_vel;
			}
			OLED_clearAll();
			for (int i = -4; i < 5; i++){
				OLED_set_pixel((int)leftPaddleX, (int)leftPaddleY + i);
				OLED_set_pixel((int)rightPaddleX, (int)rightPaddleY + i);
			}
			OLED_set_pixel((int)x, (itn)y);
			OLED_refresh();
			_delay_ms(2);
		}
	}
}
