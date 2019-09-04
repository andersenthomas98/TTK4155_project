/*
 * lab2.c
 *
 * Created: 04.09.2019 09:57:38
 *  Author: thoander
 */ 

#include "Drivers/uart.h"
#include "Drivers/xmem.h"
#define F_CPU 4915200UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#define MYUBRR 31



int main(void)
{
	UART_init(MYUBRR);
	SRAM_test();
	return 0;
	
}