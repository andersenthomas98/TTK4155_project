/*
 * timer.h
 *
 * Created: 02.10.2019 12:42:56
 *  Author: thoander
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

void timer_0division1024Init(void);
void TIM8_WriteTCNT0(uint8_t i);
unsigned int TIM8_ReadTCNT0(void);

void timer_1division256Init(void);

unsigned int TIM8_ReadTCNT2(void);

void TIM8_WriteTCNT2(uint8_t i);


#endif /* TIMER_H_ */