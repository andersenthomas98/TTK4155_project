/*
 * node2_lab8.c
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
#include "Drivers/timer.h"
#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>
//#include <avr/interrupt.h>
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
	timer_0division1024Init();
	
	while (1) {
		printf("waiting for game start\n\r");
		while (!GAME_START); // Do nothing
		printf("game starting\n\r");
		MOTOR_control();
	}

}
