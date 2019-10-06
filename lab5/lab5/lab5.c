/*
 * lab5.c
 *
 * Created: 02.10.2019 08:38:43
 *  Author: thoander
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
	btn_init();
	printf("\nStarting.... \n\r");
	timer_8bit256divisionCheckOnlyinit();
	CAN_init();

	
	
	OLED_init();
	OLED_clearAll();
	OLED_refresh();
	
	/*
	menu_t mainMenu;
	menu_ptr mainMenuPtr = &mainMenu;
	mainMenu.name = "Main menu";
	mainMenu.num_children = 3;
	mainMenu.selectedChild = 0;

	menu_t sub_menu0;
	menu_ptr sub_menu0Ptr = &sub_menu0;
	sub_menu0.parent = mainMenuPtr;
	sub_menu0.num_children = 0;
	sub_menu0.name = "sub0";

	menu_t sub_menu1;
	menu_ptr sub_menu1Ptr = &sub_menu1;
	sub_menu1.parent = mainMenuPtr;
	sub_menu1.num_children = 3;
	sub_menu1.name = "Morofunksjoner";

	menu_t sub_menu2;
	menu_ptr sub_menu2Ptr = &sub_menu2;
	sub_menu2.parent = mainMenuPtr;
	sub_menu2.num_children = 0;
	sub_menu2.name = "sub2";

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
	*/
	
	msg_t msg;
	msg.id = 0xBB10;
	msg.length = 3;
	msg_ptr msgPtr = &msg;
	
	
	//CAN_message_send(msgPtr);
	
	
	while(1) {
		_delay_ms(500);
		// Testing SPI
		/*
		SPI_transmit(0x55);
		_delay_ms(500);
		*/
		
		// Testing CAN controller
		/*
		MCP_write(MCP_RXF0SIDH, 171);
		_delay_ms(10);
		printf("MCP_read = %d\n\r", MCP_read(MCP_RXF0SIDH));
		_delay_ms(10);
		MCP_reset();
		printf("MCP_read = %d\n\r", MCP_read(MCP_RXF0SIDH));
		_delay_ms(500);
		*/
		
		// Testing CAN
		CAN_message_send(msgPtr);
		
		_delay_ms(5000);
		
		
	} 
	
	return 0;
	
}

