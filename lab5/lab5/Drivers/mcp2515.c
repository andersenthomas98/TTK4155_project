/*
 * mcp2515.c
 *
 * Created: 02.10.2019 14:13:28
 *  Author: thoander
 */ 

#include "mcp2515.h"
#include "spi.h"
#include <avr/io.h>
#define F_CPU 4915200
#include <avr/delay.h>

void MCP_init(void) {
	SPI_MasterInit();
	MCP_reset();
}


void MCP_reset(void) {
	// Initiate data transmission
	PORTB &= ~(1 << PB4);
	
	// Send RESET instruction
	SPI_transmit(MCP_RESET);
	
	// End data transmission
	PORTB |= (1 << PB4);
}


uint8_t MCP_read(uint8_t address) {
	uint8_t data;
	
	// Select CAN controller
	PORTB &= ~(1 << PB4);
	
	// Send READ instruction
	SPI_transmit(MCP_READ);
	
	// Send address
	SPI_transmit(address);
	
	// Read from address specified over
	data = SPI_read();
	
	// Deselect CAN controller
	PORTB |= (1 << PB4);
	
	return data;
	
}

void MCP_write(uint8_t address, uint8_t data) {
	// Select CAN controller
	PORTB &= ~(1 << PB4);
	
	// Send WRITE instruction
	SPI_transmit(MCP_WRITE);
	
	// Send address
	SPI_transmit(address);
	
	// Send data
	SPI_transmit(data);
	
	// Deselect CAN controller
	PORTB |= (1 << PB4);
}

void MCP_requestToSend(int buffer) {
	// Select CAN controller
	PORTB &= ~(1 << PB4);
	
	// RTS from buffer 0, 1, 2, or all
	if (buffer == 0) {
		SPI_transmit(MCP_RTS_TX0);
	}
	else if (buffer == 1) {
		SPI_transmit(MCP_RTS_TX1);
	}
	else if (buffer == 2) {
		SPI_transmit(MCP_RTS_TX2);
	}
	else {
		SPI_transmit(MCP_RTS_ALL);
	}
	
	// Deselect CAN controller
	PORTB |= (1 << PB4);
}

void MCP_bitModify(uint8_t address, uint8_t mask, uint8_t data) {
	// Select CAN controller
	PORTB &= ~(1 << PB4);
	
	// Send BIT MODIFY instruction
	SPI_transmit(MCP_BITMOD);
	
	// Send address of register
	SPI_transmit(address);
	
	// Send mask byte
	SPI_transmit(mask);
	
	// Send data byte
	SPI_transmit(data);
	
	// Deselect CAN controller
	PORTB |= (1 << PB4);
}

uint8_t MCP_readStatus(void) {
	uint8_t data;
	
	// Select CAN controller
	PORTB &= ~(1 << PB4);
	
	// Send READ STATUS instruction
	SPI_transmit(MCP_READ_STATUS);
	
	data = SPI_read();
	
	// Deselect CAN controller
	PORTB |= (1 << PB4);
	
	return data;
	
}
