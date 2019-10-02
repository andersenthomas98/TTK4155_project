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
	timer_8bit256divisionCheckOnlyinit();
	
	OLED_clearAll();

	//MENU_init();
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
	sub_menu00.name = "pong";
	sub_menu00.fun_ptr = &MENU_pong;

	menu_t sub_menu10;
	menu_ptr sub_menu10Ptr = &sub_menu10;
	sub_menu10.parent = sub_menu1Ptr;
	sub_menu10.num_children = 0;
	sub_menu10.name = "Thomas' CD";
	sub_menu10.fun_ptr = &MENU_animation;

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
	

	while(1) {
		
		
	}
	
	return 0;
	
}

