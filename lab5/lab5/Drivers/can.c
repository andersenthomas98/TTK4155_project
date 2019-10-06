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


void CAN_init(void) {
	MCP_init();
	
	// Enable recieve and message error interrupts
	MCP_write(MCP_CANINTE, 0b10000101);

	MCP_bitModify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);	//enter loopback mode
	MCP_bitModify(MCP_RXB0CTRL, 0b01100000, 0b01100000);
	
	if (MCP_read(MCP_CANCTRL) & 0b01000000) {
		printf("CAN controller in loopback mode\n\r");
	}
}

void CAN_message_send(msg_ptr msgPtr) {
	
	// Set TXB0SIDH (higher ID-register)
	MCP_write(MCP_TXB0CTRL + 1, (msgPtr->id) >> 8);
	printf("higher ID to be sent = %#X \n\r",  (msgPtr->id) >> 8);
	// Set TXB0SIDL (lower ID-register)
	MCP_write(MCP_TXB0CTRL + 2, (msgPtr->id) & 0xFF);
	printf("lower ID to be sent = %#X \n\r", (msgPtr->id) & 0xFF);
	// Set TXB0DLC (length register)
	MCP_write(MCP_TXB0CTRL + 5, (msgPtr->length));
	
	
	for (uint8_t i = MCP_TXB0CTRL + 6; i <= MCP_TXB0CTRL + 14; i++) {
		MCP_write(i, msgPtr->data[i]);
	}
	
	
	MCP_requestToSend(0);
	// Transmission of CAN msg will start when the device detects that the bus is available...
}

msg_t CAN_message_recieve(void) {
	msg_t msg;
	
	// Read ID from RXB0SIDH and RXB0SIDL
	uint16_t lowerId = MCP_read(MCP_RXB0CTRL + 2);
	uint16_t upperId = MCP_read(MCP_RXB0CTRL + 1);
	printf("recieved lower ID = %#X \n\r", lowerId);
	printf("recieved upper ID = %#X \n\r", upperId);
	msg.id =  (upperId << 8) + lowerId;
	
	// Read length from RXB0DLC
	msg.length = MCP_read(MCP_RXB0CTRL + 5);
	
	// Read data
	for (uint8_t i = MCP_RXB0CTRL + 6; i <= MCP_RXB0CTRL + 14; i++) {
		msg.data[i] = MCP_read(i);
	}
	return msg;
} 
