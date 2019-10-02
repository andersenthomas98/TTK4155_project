/*
 * adc.h
 *
 * Created: 11.09.2019 15:28:28
 *  Author: thoander
 */ 

#include <stdint.h>

#ifndef ADC_H_
#define ADC_H_


uint8_t ADC_read_x(void);

uint8_t ADC_read_y(void);

uint8_t ADC_slider_left(void);

uint8_t ADC_slider_right(void);

#endif /* ADC_H_ */