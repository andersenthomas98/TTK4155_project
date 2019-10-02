/*
 * timer.h
 *
 * Created: 02.10.2019 12:42:56
 *  Author: thoander
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

void timer_8bit256divisionCheckOnlyinit(void);
void TIM8_WriteTCNT0(uint8_t i);
unsigned int TIM8_ReadTCNT0(void);


#endif /* TIMER_H_ */