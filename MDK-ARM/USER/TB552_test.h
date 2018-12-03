#ifndef _TB552_TEST_H
#define _TB552_TEST_H

#include "stdio.h"
#include <stdlib.h>		//strtolÍ·ÎÄ¼þ 
#include "stm32f1xx_hal.h"
#include "string.h"
#include <stdio.h>

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart4;

extern volatile uint8_t rx_len;
extern volatile uint8_t recv_end_flag;
extern uint8_t  rx_buffer[100];
extern char 		BUFFER_SIZE;

void comm(void);
void Get_Gpio(void);
void Cont_Gpio(void);
void Data_Turn(void);


#endif

