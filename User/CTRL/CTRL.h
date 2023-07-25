#ifndef __CTRL_H
#define __CTRL_H

#include "main.h"

#define MOTO_L_PWM  TIM4->CCR1
#define MOTO_R_PWM  TIM4->CCR3

#define MOTO_L1(x) GPIO_WriteBit(GPIOA, GPIO_Pin_3, (BitAction)(x));
#define MOTO_L2(x) GPIO_WriteBit(GPIOA, GPIO_Pin_2, (BitAction)(x));
#define MOTO_R1(x) GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)(x));
#define MOTO_R2(x) GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction)(x));

void MOTO_Ctrl(uint16_t MOTO_L, uint16_t MOTO_R);
void Ctrl_Init(void);


#endif
