/*
 * adc.h
 *
 * Created: 11.09.2019 15:28:28
 *  Author: thoander
 */ 

#include <stdint.h>

#ifndef ADC_H_
#define ADC_H_


typedef struct {
	uint8_t x;
	uint8_t y;
} pos_t;

typedef enum {
	LEFT, RIGHT, UP, DOWN, NEUTRAL
} dir_t;

uint8_t ADC_read_x(void);

uint8_t ADC_read_y(void);



#endif /* ADC_H_ */