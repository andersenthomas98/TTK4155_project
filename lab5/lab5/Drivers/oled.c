/*
 * oled.c
 *
 * Created: 18.09.2019 11:54:52
 *  Author: thoander
 */ 

#include "oled.h"
#include "xmem.h"
#include "fonts.h"
#include <avr/io.h>


void OLED_init(void) {
	XMEM_write(0xAE, 0xAE); // display off
	XMEM_write(0xA1, 0xA1); // segment remap
	XMEM_write(0xDA, 0xDA); // common pads hardware: alternative
	XMEM_write(0x12, 0x12);
	XMEM_write(0xC8, 0xC8); // common output scan direction:com63-com0
	XMEM_write(0xA8, 0xA8); //multiplex ratio mode:63 
	XMEM_write(0x3F, 0x3F); 
	XMEM_write(0xD5, 0xD5); // display divide ratio/osc. freq. mode
	XMEM_write(0x80, 0x80);
	XMEM_write(0x81, 0x81); // contrast control
	XMEM_write(0x50, 0x50);
	XMEM_write(0xD9, 0xD9); // set pre-charge period
	XMEM_write(0x21, 0x21); 
	XMEM_write(0x20, 0x20); // set page addressing mode
	XMEM_write(0x02, 0x02); 
	XMEM_write(0xDB, 0xDB); // VCOM deselect level mode
	XMEM_write(0x30, 0x30);
	XMEM_write(0xAD, 0xAD); // master config
	XMEM_write(0x00, 0x00);
	XMEM_write(0xA4, 0xA4); // out follows RAM content
	XMEM_write(0xA6, 0xA6); // set normal display
	XMEM_write(0xD3, 0xD3);
	XMEM_write(0x00, 0x00);
	XMEM_write(0xAF, 0xAF); // display on
}

void OLED_pos(uint8_t page, uint8_t col) { // x går fra 0 - 127, y går fra 0 - 63
	if (page >= 0 && page < 8 && col >= 0 && col < 128) {
		uint8_t lowerCol = col & 0x0F;
		uint8_t upperCol = col >> 4;
	
		XMEM_write(0xB0 + page, 0xB0 + page);  // Set page in command register
		XMEM_write(lowerCol, lowerCol);		// Set lower column start address
		XMEM_write(0x10 + upperCol, 0x10 + upperCol);   // Set higher column start address
	}
}



void OLED_print_char(char c, int offset) {
	c -= 32; // ASCII offset 
	for (int row = 0; row < 8; row++) {
		//printf("\n\r%X0", pgm_read_byte(&font8[c][row]));
		XMEM_write(pgm_read_byte(&font8[c][row]), 0x800 + row + offset);
	}
}

void OLED_print_string(char *c, int offset) {
	int i = 0;
	while (c[i] != '\0') {
		OLED_print_char(c[i], i*8 + offset);
		i++;
	}
}

void OLED_set_pixel(int x, int y){
	if (x < 128 && x >= 0 && y < 64 && y >= 0){
		int page = y/8;
		int height = y - page*8;
		uint16_t index = 0x800 + page*128 + x;
		uint8_t value = XMEM_read(index);
		value |= (1 << height);
		XMEM_write(value, index);
	}
}

void OLED_reset_pixel(int x, int y){
	if (x < 128 && x >= 0 && y < 64 && y >= 0){
	int page = y/8;
	int height = y - page*8;
	uint16_t index = 0x800 + page*128 + x;
	uint8_t value = XMEM_read(index);
	value &= ~(1 << height);
	XMEM_write(value, index);
	}
}


void OLED_refresh(void){
	for (int page = 0; page < 8; page++){
		XMEM_write(0xB0 + page, 0xB0 + page);  // Set command register
		XMEM_write(0, 0);		// Set lower column start address
		XMEM_write(0x10, 0x10);  // Set data register
		for (int column = 0; column < 128; column++){
			uint8_t SRAMvalue = XMEM_read(0x800 + page*128 + column);
			XMEM_write(SRAMvalue, 0x200 + SRAMvalue);
		}
	}
}


void OLED_clearAll(void) {
	for (uint16_t index = 0x800; index < 0x800 + 1024; index++){
		XMEM_write(0, index);
	}
}

void OLED_setBrightness(uint8_t level) {
	XMEM_write(0x81, 0x81);
	XMEM_write(level, level);
}