/*
 * frame.h
 *
 *  Created on: Dec 8, 2017
 *      Author: lidq
 */

#ifndef SRC_INCLUDE_FRAME_H_
#define SRC_INCLUDE_FRAME_H_

#include <typedef.h>
#include <uart.h>

#define	FW_POS_START1                         	0
#define	FW_POS_START2	                      	1
#define	FW_POS_LEN	                      		2
#define	FW_POS_DATA	                      		3
#define	FW_POS_CRC1  	                      	15
#define	FW_POS_CRC2  	                      	16
#define	FW_POS_END1  	                     	17
#define	FW_POS_END2  	                     	18

#define FW_BYTE_HEAD_1                         	0X55
#define FW_BYTE_HEAD_2                         	0XAA
#define FW_BYTE_END_1                          	0XA5
#define FW_BYTE_END_2		                   	0X5A

#define FW_HEAD                                 0
#define FW_LEN    								1
#define FW_END    								2

u16 crc16_value(u8 *buff, u8 len);

int crc16_check(u8 *buff, u8 len, u16 crc16);

int frame_send_rc_data(u16 *rc_data);

#endif /* SRC_INCLUDE_FRAME_H_ */
