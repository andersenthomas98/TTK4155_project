/*
 * can.h
 *
 * Created: 04.10.2019 18:03:08
 *  Author: thoander
 */ 


#ifndef CAN_H_
#define CAN_H_
#include <stdint.h>

typedef struct CAN_message {
		uint16_t id;
		uint8_t length;
		uint8_t data[8];
}msg_t, *msg_ptr;

void CAN_init(void);

void CAN_message_send(msg_ptr);

msg_t CAN_message_recieve(void);

#endif /* CAN_H_ */