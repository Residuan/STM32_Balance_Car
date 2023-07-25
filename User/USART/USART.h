#ifndef __USART_H
#define __USART_H

#include "main.h"

void USART_Config(uint32_t BaudRate);
void USART_SendString(USART_TypeDef* USARTx, char *DataString);
void USART_SendNumBer(uint32_t Num, uint8_t size);
void USART_SendArray(uint8_t *Array, uint16_t size);
void USART_SendByet(uint8_t data);





#endif
