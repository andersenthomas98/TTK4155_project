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
	// Set PB4 (/SS), PB5 (MOSI) and PB7 (SCK) as output
	DDRB |= (1 << DDB4) | (1 << DDB5) | (1 << DDB7);
	
	// Set PB6 (MISO) as input
	DDRB &= ~(1 << DDB6);
	
	// Select Master SPI mode, SPI enable, SPI interrupt enable (Global interrupts must be enabled)
	SPCR |= (1 << MSTR) | (1 << SPE); //| (1 << SPIE);

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
