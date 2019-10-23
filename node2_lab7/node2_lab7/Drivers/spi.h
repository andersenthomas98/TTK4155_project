/*
 * spi.h
 *
 * Created: 02.10.2019 09:53:49
 *  Author: thoander
 */ 


#ifndef SPI_H_
#define SPI_H_
#include <stdint.h>

void SPI_MasterInit(void);
void SPI_transmit(uint8_t data);
uint8_t SPI_read(void);


#endif /* SPI_H_ */