/*
 * CFile1.c
 *
 * Created: 04.10.2019 14:55:19
 *  Author: thoander
 */ 

#include "adc.h"
#include "menu.h"
#include "oled.h"
#include "controls.h"
#include "timer.h"
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#define F_CPU 4915200
#include <util/delay.h>

void pong_fast() {
	uint8_t SRAMvalue;
	
	float x = 63;
	float y = 31;
	float x_vel = 0.5;
	float y_vel = 0;
	float xPrev = x;
	float yPrev = y;

	uint8_t leftPaddleX = 3;
	uint8_t leftPaddleY = 31;
	uint8_t lowerColLeftPaddle = 3 & 0x0F;	//left paddle
	uint8_t upperColLeftPaddle = 3 >> 4;

	uint8_t rightPaddleX = 124;
	uint8_t rightPaddleY = 31;
	uint8_t lowerColRightPaddle = 124 & 0x0F;	//left paddle
	uint8_t upperColRightPaddle = 124 >> 4;

	int rightPoints = 0;
	int leftPoints = 0;
	float difference = 0;

	OLED_clearAll();
	OLED_refresh();

	while (1) {
		float x = 63;
		float y = 31;
		x_vel = 1;
		y_vel = 0;
		while (1) {
			TIM8_WriteTCNT0(0);
			rightPaddleY = (ADC_slider_right()) / 4;
			leftPaddleY = (ADC_slider_left()) / 4;
			xPrev = x;
			yPrev = y;
			
			OLED_reset_pixel((int)xPrev, (int)yPrev);	//clears last ball location
			
			XMEM_write(0xB0 + (int)yPrev/8, 0xB0 + (int)yPrev/8);	//set page to ball-page
			XMEM_write((int)xPrev & 0x0F, (int)xPrev & 0x0F);		// Set lower column start address
			XMEM_write(0x10 + ((int)xPrev >> 4), 0x10 + ((int)xPrev >> 4));  // Set upper column address
			
			SRAMvalue = XMEM_read(0x800 + (int)yPrev/8 * 128 + (int)xPrev);	//remove old ball
			XMEM_write(SRAMvalue, 0x200 + SRAMvalue);
			
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
			else if (x == leftPaddleX + 1 && y <= leftPaddleY + 4 && y >= leftPaddleY - 4) {
				difference = y - leftPaddleY;
				y_vel = difference / 8.0;
				x_vel = 0.5;
			}
			else if (x == rightPaddleX - 1 && y <= rightPaddleY + 4 && y >= rightPaddleY - 4) {
				difference = y - rightPaddleY;
				y_vel = difference / 8.0;
				x_vel = -0.5;
			}
			if (y <= 0 || y >= 63) {
				y_vel = -y_vel;
			}

			for (int page = 0; page < 8; page++) {	//clears buffer along paddle-x-axes
				XMEM_write(0, 0x800 + page * 128 + 3);
				XMEM_write(0, 0x800 + page * 128 + 124);
			}

			for (int i = -4; i < 5; i++) {
				OLED_set_pixel(leftPaddleX, leftPaddleY + i);
				OLED_set_pixel(rightPaddleX, rightPaddleY + i);
			}
			OLED_set_pixel((int)x, (int)y);	//sets current ball c
			OLED_reset_pixel((int)xPrev, (int)yPrev);	//clears last ball location




			for (int page = 0; page < 8; page++) {	//set OLED along left paddle column
				XMEM_write(0xB0 + page, 0xB0 + page);  // Set command register

				XMEM_write(lowerColLeftPaddle, lowerColLeftPaddle);		// Set lower column start address
				XMEM_write(0x10 + upperColLeftPaddle, 0x10 + upperColLeftPaddle);  // Set upper column address

				SRAMvalue = XMEM_read(0x800 + page * 128 + leftPaddleX);
				XMEM_write(SRAMvalue, 0x200 + SRAMvalue);

				XMEM_write(lowerColRightPaddle, lowerColRightPaddle);		//do the same for the right paddle
				XMEM_write(0x10 + upperColRightPaddle, 0x10 + upperColRightPaddle);

				SRAMvalue = XMEM_read(0x800 + page * 128 + rightPaddleX);
				XMEM_write(SRAMvalue, 0x200 + SRAMvalue);

			}

			XMEM_write(0xB0 + (int)y/8, 0xB0 + (int)y/8);	//set page to ball-page
			XMEM_write((int)x & 0x0F, (int)x & 0x0F);		// Set lower column start address
			XMEM_write(0x10 + ((int)x >> 4), 0x10 + ((int)x >> 4));  // Set upper column address
			
			SRAMvalue = XMEM_read(0x800 + (int)y/8 * 128 + (int)x);	//set new ball
			XMEM_write(SRAMvalue, 0x200 + SRAMvalue);
			
			//printf("Time elapsed: %d", TIM8_ReadTCNT0());
			while (TIM8_ReadTCNT0() < 20){
				
			}
		}
		
		OLED_clearAll();
		OLED_print_char(rightPoints + 48, 128 * 3 + 50);
		OLED_print_char(leftPoints + 48, 128 * 3 + 70);
		OLED_refresh();
		_delay_ms(2000);
		OLED_clearAll();
		OLED_refresh();
	}
}

void pong_slow() {
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
			TIM8_WriteTCNT0(0);
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
			OLED_set_pixel((int)x, (int)y);
			TIM8_WriteTCNT0(0);
			OLED_refresh();
			printf("Time elapsed: %d", 256 + TIM8_ReadTCNT0());
			
		}
		OLED_clearAll();
		OLED_print_char(rightPoints + 48, 128 * 3 + 50);
		OLED_print_char(leftPoints + 48, 128 * 3 + 70);
		OLED_refresh();
		_delay_ms(2000);
		OLED_clearAll();
		OLED_refresh();
	}
} 