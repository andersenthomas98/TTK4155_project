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
	
	while(1){
 		_delay_ms(500);
	}
	
}

