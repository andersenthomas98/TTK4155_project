/*
 * dac.h
 *
 * Created: 30.10.2019 12:41:24
 *  Author: annemmat
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_
#include <stdint.h>

void MOTOR_init(void);
void MOTOR_DAC_write(uint8_t d);
void MOTOR_set(uint8_t speed, int dir);
uint16_t MOTOR_encoder_read(void);

#endif /* MOTOR_H_ */