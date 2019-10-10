/*
 * node2_lab6.c
 *
 * Created: 09.10.2019 13:56:40
 *  Author: axeltb
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "Drivers/can.h"
#include "Drivers/interrupt.h"
#include "Drivers/mcp2515.h"
#include "Drivers/spi.h"
#include "Drivers/uart.h"
#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#define MYUBRR 103

int main(void)
{
	INTERRUPT_init();
	UART_init(MYUBRR);
	CAN_init(MODE_NORMAL);
	
	msg_t msg;
	msg.id = 0xC1;
	msg.length = 3;
	msg.data[0] = 0xB;
	msg.data[1] = 0xF;
	msg_ptr msgPtr = &msg;
	
    while(1)
    {	
		//CAN_message_send(msgPtr);
		
		_delay_ms(6000);
		
    }
}