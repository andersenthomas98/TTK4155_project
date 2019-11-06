/*
 * oled.h
 *
 * Created: 18.09.2019 12:24:04
 *  Author: thoander
 */ 

#include <stdint.h>

#ifndef OLED_H_
#define OLED_H_

void OLED_init(void);
void OLED_pos(uint8_t x, uint8_t y);
void OLED_print_char(char c, int offset);
void OLED_print_string(char *c, int offset);
void OLED_clearAll(void);
void OLED_setBrightness(uint8_t level);

void OLED_set_pixel(int x, int y);
void OLED_reset_pixel(int x, int y);
void OLED_refresh(void);



#endif /* OLED_H_ */