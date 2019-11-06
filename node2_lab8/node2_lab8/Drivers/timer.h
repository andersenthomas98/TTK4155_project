/*
 * timer.h
 *
 * Created: 06.11.2019 13:24:58
 *  Author: axeltb
 */ 


#ifndef TIMER_H_
#define TIMER_H_

void timer_0division1024Init(void);
void TIM8_WriteTCNT0(uint8_t i);
unsigned int TIM8_ReadTCNT0(void);

void timer_3division256Init();



#endif /* TIMER_H_ */