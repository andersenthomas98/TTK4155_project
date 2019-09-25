/*
 * xmem.h
 *
 * Created: 04.09.2019 15:50:51
 *  Author: thoander
 */ 


#ifndef XMEM_H_
#define XMEM_H_
#include <stdint.h>

void XMEM_init(void);
uint8_t XMEM_read(uint16_t address);
void XMEM_write(uint8_t data, uint16_t address);
void SRAM_test(void);




#endif /* XMEM_H_ */