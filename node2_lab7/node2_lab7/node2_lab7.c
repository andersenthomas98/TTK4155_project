/*
 * node2_lab7.c
 *
 * Created: 23.10.2019 10:19:40
 *  Author: thoander
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "Drivers/can.h"
#include "Drivers/interrupt.h"
#include "Drivers/mcp2515.h"
#include "Drivers/spi.h"
#include "Drivers/uart.h"
#include "Drivers/pwm.h"
#include "Drivers/IR.h"
#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#define MYUBRR 103

int main(void)
{
	
	UART_init(MYUBRR);
	printf("Node 2 starting...\n\r");
	INTERRUPT_init();
	CAN_init(MODE_NORMAL);
	PWM_init();
	IR_init();
	MOTOR_init();
	
	
	msg_t msg;
	msg.id = 0xC1;
	msg.length = 3;
	msg.data[0] = 0xB;
	msg.data[1] = 0xF;
	msg_ptr msgPtr = &msg;
	
	while(1)
	{
		MOTOR_encoder_read();
		_delay_ms(30);
	}
}