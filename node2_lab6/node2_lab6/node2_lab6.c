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
#define MYUBRR 103

int main(void)
{
	UART_init(MYUBRR);
	INTERRUPT_init();
	CAN_init();
	
	msg_t msg;
	msg.id = 0xA5;
	msg.length = 3;
	msg.data[0] = 0xC;
	msg.data[1] = 0xF;
	msg_ptr msgPtr = &msg;
	
    while(1)
    {
		printf("new iteration\n\r");
        CAN_message_send(msgPtr);
		_delay_ms(1000);
    }
}