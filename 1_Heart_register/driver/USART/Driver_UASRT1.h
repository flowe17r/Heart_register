#ifndef __Driver_USART_H
#define __Driver_USART_H

#include "stm32f10x.h"
#include "stdio.h"

void Driver_UASRT1_Init(void);
void Driver_USART1_Start(void);
void Driver_USART1_Stop(void);

void Driver_USART1_Sendchar(uint8_t c);
void Driver_USART1_SendString(uint8_t *str,uint16_t len);

#endif //Driver_USART_H
