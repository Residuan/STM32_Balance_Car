#include "ENCODE.h"

void RENCODE_Config(void)
{
    TIM_TimeBaseInitTypeDef Time_TimeBaseInitStructure;
    TIM_ICInitTypeDef   TIM_ICInitStructure;
    GPIO_InitTypeDef    GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    Time_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    Time_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    Time_TimeBaseInitStructure.TIM_Period = 65535;
    Time_TimeBaseInitStructure.TIM_Prescaler = 0;
    TIM_TimeBaseInit(TIM2, &Time_TimeBaseInitStructure);

    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter = 0xF;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICFilter = 0xF;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);

    TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12,TIM_ICPolarity_Falling, TIM_ICPolarity_Rising);

    TIM_Cmd(TIM2, ENABLE);
}

void LENCODE_Config(void)
{
    TIM_TimeBaseInitTypeDef Time_TimeBaseInitStructure;
    TIM_ICInitTypeDef   TIM_ICInitStructure;
    GPIO_InitTypeDef    GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    Time_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    Time_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    Time_TimeBaseInitStructure.TIM_Period = 65535;
    Time_TimeBaseInitStructure.TIM_Prescaler = 0;
    TIM_TimeBaseInit(TIM3, &Time_TimeBaseInitStructure);

    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter = 0xF;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICFilter = 0xF;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);

    TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12,TIM_ICPolarity_Falling, TIM_ICPolarity_Rising);

    TIM_Cmd(TIM3, ENABLE);
}

void ENCODE_Config(void)
{
    RENCODE_Config();
    LENCODE_Config();
}


int16_t Get_REncoder(void)
{
    int16_t Temp1 = TIM_GetCounter(TIM2);
    TIM2->CNT = 0;
    return Temp1;
}

int16_t Get_LEncoder(void)
{
    int16_t Temp2 = TIM_GetCounter(TIM3);
    TIM3->CNT = 0;
    return Temp2;
}




