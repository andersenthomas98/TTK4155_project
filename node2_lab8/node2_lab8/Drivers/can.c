/*
 * can.c
 *
 * Created: 04.10.2019 18:02:51
 *  Author: thoander
 */ 

#include "can.h"
#include "mcp2515.h"
#include <stdlib.h>
#include <stddef.h>
#include "uart.h"
#include <avr/interrupt.h>


void CAN_init(uint8_t mode) {
	MCP_init();
	
	// Enable receive and transmit interrupts
	MCP_write(MCP_CANINTE, 0b00000101); // HVORFOR MÅ VI GJØRE DETTE TO GANGER?
	MCP_bitModify(MCP_CANINTE, 0b00000101, 0b10000101);
	printf("interrupts for mcp = %#X \n\r", MCP_read(MCP_CANINTE));
	
	MCP_bitModify(MCP_CANCTRL, MODE_MASK, mode);	//enter specified mode
	MCP_bitModify(MCP_RXB0CTRL, 0b01100000, 0b01100000); // Turn mask/filters off, recieve any message
	
	if (MCP_read(MCP_CANCTRL) & MODE_LOOPBACK) {
		printf("CAN controller in loopback mode\n\r");
	}
}

void CAN_message_send(msg_ptr msgPtr) {
	cli();
	// Set TXB0SIDH (higher ID-register)
	MCP_write(MCP_TXB0CTRL + 1, (msgPtr->id));
	
	// Set TXB0DLC (length register)
	MCP_write(MCP_TXB0CTRL + 5, (msgPtr->length));
	
	int dataIterator = 0;
	for (uint8_t i = MCP_TXB0CTRL + 6; i <= MCP_TXB0CTRL + 6 + msgPtr->length; i++) {
		MCP_write(i, msgPtr->data[dataIterator]);
		dataIterator++;
	}
	MCP_requestToSend(0);
	// Transmission of CAN msg will start when the device detects that the bus is available...
	sei();
}

msg_t CAN_message_recieve(void) {
	msg_t msg;
	
	// Read ID from RXB0SIDH and RXB0SIDL
	uint8_t upperId = MCP_read(MCP_RXB0CTRL + 1);
	
	msg.id = upperId ;
	
	// Read length from RXB0DLC
	msg.length = MCP_read(MCP_RXB0CTRL + 5);
	
	// Read data
	int dataIterator = 0;
	for (uint8_t i = MCP_RXB0CTRL + 6; i <= MCP_RXB0CTRL + 6 + msg.length; i++) {
		msg.data[dataIterator] = MCP_read(i);
		dataIterator++;
	}
	return msg;
} 
