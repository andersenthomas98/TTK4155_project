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
#include "timer.h"
#include "pong.h"
#include "can.h"
#include "interrupt.h"
#include <avr/io.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#define F_CPU 4915200
#include <util/delay.h>

int firstPlace = 0;
int secondPlace = 0;
int thirdPlace = 0;


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
		printf("currentMenu = %15s\r", currentMenu->name);
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
				case LEFT:
					if (currentMenu->parent != NULL){
						currentMenu = currentMenu->parent;
					}
					break;
				case RIGHT:
					if (currentMenu->children[currentMenu->selectedChild]->num_children == 0){
						OLED_clearAll();
						currentMenu->children[currentMenu->selectedChild]->fun_ptr();
						_delay_ms(50);
					}
					else{
						currentMenu = currentMenu->children[currentMenu->selectedChild];
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
		else if (joystick_dir() == LEFT){
			XMEM_write(0xA6, 0xA6);
			return;
		}
		else{
			XMEM_write(0xA6, 0xA6);
		}
	}
}

void MENU_localHighScores(){
	OLED_clearAll();
	OLED_print_string("HIGH SCORES", 16);
	
	volatile char str[8];
	sprintf(str, "%d", firstPlace);
	OLED_print_string(&str, 2 * 128);
	sprintf(str, "%d", secondPlace);
	OLED_print_string(&str, 3 * 128);
	sprintf(str, "%d", thirdPlace);
	OLED_print_string(&str, 4 * 128);
	OLED_refresh();
	
	while(joystick_dir() != LEFT){
	}
	return;
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

void MENU_playGame(void) {
	GAME_SCORE = 0;

	uint8_t currentSliderValue = ADC_slider_right();
	uint8_t lastSliderValue = currentSliderValue;

	int currentButtonValue = btn_right();
	int lastButtonValue = currentButtonValue;

	int currentJoystickValue =  (ADC_read_x()*100/256);
	int lastJoystickValue = currentJoystickValue;
	
	OLED_clearAll();
	OLED_print_string("Playing game", 128*1 + 20);
	OLED_refresh();
	
	msg_t msg;
	msg.id = 0x04;
	msg.length = 1;
	msg_ptr msgPtr = &msg;
	CAN_message_send(msgPtr);	//tell the game to start
	
	timer_1division256Init(); //start our timer
	while (GAME_OVER != 1) {
		TIM8_WriteTCNT0(0);
		
		currentSliderValue = ADC_slider_right();

		
		currentJoystickValue =  (ADC_read_x()*100/256);

		
		currentButtonValue = btn_right();

		if ((abs(currentSliderValue - lastSliderValue) > 1) || (abs(currentJoystickValue - lastJoystickValue) > 5) || (currentButtonValue != lastButtonValue)){	//only send new values
			send_slider_joystick_button(currentSliderValue, currentJoystickValue, currentButtonValue);
			lastSliderValue = currentSliderValue;
			lastJoystickValue = currentJoystickValue;
			lastButtonValue = currentButtonValue;
		}
		// Update up to 24 times per second
		while (TIM8_ReadTCNT0() < 200);
		//printf("iteration\r");
	}

	TIMSK &= ~(1 << OCIE1A);
	printf("GAME OVER\r\n");
	OLED_clearAll();
	volatile char str[8];
	sprintf(str, "%d", GAME_SCORE);
	OLED_print_string(str, 128 * 4 + 60);
	OLED_print_string("GAME OVER", 128 * 2 + 30);
	OLED_refresh();
	GAME_OVER = 0;

	if (GAME_SCORE > firstPlace){
		thirdPlace = secondPlace;
		secondPlace = firstPlace;
		firstPlace = GAME_SCORE;
	}
	else if (GAME_SCORE > secondPlace){
		thirdPlace = secondPlace;
		secondPlace = GAME_SCORE;
	}
	else if (GAME_SCORE > thirdPlace){
		thirdPlace = GAME_SCORE;
	}
	_delay_ms(3000);
	return;
}


void MENU_start(void) {
	OLED_init();
	OLED_clearAll();
	OLED_refresh();

	menu_t mainMenu;
	menu_ptr mainMenuPtr = &mainMenu;
	mainMenu.name = "Main menu";
	mainMenu.num_children = 3;
	mainMenu.selectedChild = 0;
	
	menu_t sub_menu0;
	menu_ptr sub_menu0Ptr = &sub_menu0;
	sub_menu0.parent = mainMenuPtr;
	sub_menu0.num_children = 0;
	sub_menu0.name = "Start spill";
	sub_menu0.fun_ptr = &MENU_playGame;
	
	menu_t sub_menu1;
	menu_ptr sub_menu1Ptr = &sub_menu1;
	sub_menu1.parent = mainMenuPtr;
	sub_menu1.num_children = 3;
	sub_menu1.name = "Morofunksjoner";
	
	menu_t sub_menu2;
	menu_ptr sub_menu2Ptr = &sub_menu2;
	sub_menu2.parent = mainMenuPtr;
	sub_menu2.num_children = 0;
	sub_menu2.name = "High Scores";
	sub_menu2.fun_ptr = &MENU_localHighScores;
	
	mainMenu.parent = NULL;
	mainMenu.children[0] = sub_menu0Ptr;
	mainMenu.children[1] = sub_menu1Ptr;
	mainMenu.children[2] = sub_menu2Ptr;
	
	menu_t sub_menu00;
	menu_ptr sub_menu00Ptr = &sub_menu00;
	sub_menu00.parent = sub_menu1Ptr;
	sub_menu00.num_children = 0;
	sub_menu00.name = "quick pong";
	sub_menu00.fun_ptr = &pong_fast;
	
	menu_t sub_menu10;
	menu_ptr sub_menu10Ptr = &sub_menu10;
	sub_menu10.parent = sub_menu1Ptr;
	sub_menu10.num_children = 0;
	sub_menu10.name = "slow pong";
	sub_menu10.fun_ptr = &pong_slow;
	
	menu_t sub_menu20;
	menu_ptr sub_menu20Ptr = &sub_menu20;
	sub_menu20.parent = sub_menu1Ptr;
	sub_menu20.num_children = 0;
	sub_menu20.name = "Invers";
	sub_menu20.fun_ptr = &MENU_veryFunInvertingFunction;
	sub_menu1.children[0] = sub_menu00Ptr;
	sub_menu1.children[1] = sub_menu10Ptr;
	sub_menu1.children[2] = sub_menu20Ptr;
	
	MENU_navigate(mainMenuPtr);
}