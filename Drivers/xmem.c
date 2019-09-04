/*
 * xmem.c
 *
 * Created: 04.09.2019 15:50:35
 *  Author: thoander
 */ 


#include <util/delay.h>
#include <stdlib.h>
#include <avr/io.h>
#include "xmem.h"
#include "uart.h"
#define BASE_ADDRESS 0x1000

void XMEM_init(void) {
	// Enable XMEM
	MCUCR |= (1 << SRE);
	
	// SFIOR = XX100XXX
	// We use PC7-PC4 for JTAG, NOT for XMEM address
	SFIOR |= (1 << XMM2);
	SFIOR &= ~((1 << XMM1) | (1 << XMM0));
}

uint8_t XMEM_read(uint16_t address) {
	volatile uint8_t *ext_mem = (uint8_t*) BASE_ADDRESS;
	return ext_mem[address];
}

void XMEM_write(uint8_t data, uint16_t address) {
	volatile uint8_t *ext_mem = (uint8_t *) BASE_ADDRESS;
	ext_mem[address] = data;
}

void SRAM_test(void)
{
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size = 0x800;
	uint16_t write_errors = 0;
	uint16_t retrieval_errors = 0;
	printf("Starting SRAM test...\n");
	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	uint16_t seed = rand();
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i,
			retreived_value, some_value);
			write_errors++;
		}
	}
	// Retrieval phase: Check that no values were changed during or after the write phase
	srand(seed); // reset the PRNG to the state it had before the write phase
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n",
			i, retreived_value, some_value);
			retrieval_errors++;
		}
	}
	printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase\n\n", write_errors, retrieval_errors);
}