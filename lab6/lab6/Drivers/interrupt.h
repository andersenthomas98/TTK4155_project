/*
 * interrupt.h
 *
 * Created: 11.09.2019 15:28:43
 *  Author: thoander
 */ 



#ifndef INTERRUPT_H_
#define INTERRUPT_H_

extern volatile int ADC_INTERRUPT_READY;

//extern volatile int SPI_TRANSMISSION_COMPLETE;

void INTERRUPT_init();


#endif /* INTERRUPT_H_ */