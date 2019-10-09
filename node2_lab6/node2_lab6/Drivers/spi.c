/*
 * spi.c
 *
 * Created: 02.10.2019 09:53:35
 *  Author: thoander
 */ 

#include "spi.h"
#include "interrupt.h"
#include <avr/io.h>

void SPI_MasterInit(void) {
	// Set PB0 (/SS), PB2 (MOSI) and PB1 (SCK) as output
	DDRB |= (1 << DDB0) | (1 << DDB2) | (1 << DDB1);
	
	// Set PB3 (MISO) as input
	DDRB &= ~(1 << DDB3);
	
	// Select Master SPI mode, SPI enable
	SPCR |= (1 << MSTR) | (1 << SPE);
	
	// Transmit MSB of the data word first
	SPCR &= ~(1 << DORD);
	
	// Configure clock polarity (SCK is low when idle)
	SPCR &= ~(1 << CPOL);
	
	// Configure clock phase (data is sampled on leading edge)
	SPCR &= ~(1 << CPHA);
	
	// Configure SCK rate (f_osc/4)
	SPCR &= ~(1 << SPR0);
	SPCR &= ~(1 << SPR1);
}

void SPI_transmit(uint8_t data) {
	// Initiate data transmission
	SPDR = data;
	
	// Wait for transmission complete
	while (!(SPSR & (1 << SPIF)));
}	

uint8_t SPI_read(void) {
	SPDR = 0xFF; // Send dummy byte
	
	// Wait for transmission complete
	while (!(SPSR & (1 << SPIF)));
	
	return SPDR;
	// SPIF bit in SPSR register is reset when accessing SPDR
}
