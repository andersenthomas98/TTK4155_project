/*
 * lab8.c
 *
 * Created: 11.10.2019 14:24:29
 * Author : thoander
 */ 


#include "Drivers/uart.h"
#include "Drivers/xmem.h"
#include "Drivers/interrupt.h"
#include "Drivers/adc.h"
#include "Drivers/controls.h"
#include "Drivers/menu.h"
#include "Drivers/timer.h"
#include "Drivers/pong.h"
#include "Drivers/spi.h"
#include "Drivers/mcp2515.h"
#include "Drivers/can.h"
#define F_CPU 4915200
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "Drivers/oled.h"
#define MYUBRR 31


int main(void)
{
	INTERRUPT_init();
	UART_init(MYUBRR);
	XMEM_init();
	//btn_init();
	printf("\nStarting.... \n\r");
	timer_0division1024Init();
	timer_2division1024Init();
	CAN_init(MODE_NORMAL);
	
	MENU_start();
	
	
/*
	msg_t msg;
	msg.id = 0x01;
	msg.length = 1;
	msg_ptr msgPtr = &msg;
	
	uint8_t joystickDirection;
	
	//CAN_message_send(msgPtr);
	
	while(1) {
		// Testing CAN
	
		//send_joystick_dir();
		printf("current timer value = %d \n\r", TIM8_ReadTCNT0());
		//printf("interrupt flags: %#X \n\r", TIFR);
		_delay_ms(4000);
		
	} 
	
	return 0;*/
	
	//pos_t pos = joystick_pos();
	while(1){
		//send_joystick_pos();
// 		printf("joystickvalue y = %d \n\r", pos.y);
 		_delay_ms(500);
// 		pos = joystick_pos();
		//printf("iteration");
	}
	
}

