/*
 * lab4.c
 *
 * Created: 18.09.2019 08:33:21
 *  Author: thoander
 */ 


#include "Drivers/uart.h"
#include "Drivers/xmem.h"
#include "Drivers/interrupt.h"
#include "Drivers/adc.h"
#include "Drivers/controls.h"
#define F_CPU 4915200
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "Drivers/oled.h"
#define MYUBRR 31


int main(void)
{
	UART_init(MYUBRR);
	XMEM_init();
	INTERRUPT_init();
	btn_init();
	printf("Starting....\n\r");
	OLED_init();
	
	OLED_clearAll();
	
	
	OLED_pos(0,0);
	OLED_print_string("Hei axel!");
	OLED_pos(1,40);
	OLED_print_string("yoyoyo");

	OLED_init_arr();
	OLED_set_pixel(50,50);
	OLED_set_pixel(51,51);
	OLED_set_pixel(52,52);
	OLED_set_pixel(53,53);
	OLED_set_pixel(54,54);
	OLED_set_pixel(55,55);
	OLED_refresh();
	
	
	while(1) {
		
		
	}
	
	return 0;
	
}