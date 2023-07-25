#include "TIM.h"

void NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);
}

void PWM_Config(void)
{
    TIM_TimeBaseInitTypeDef Time_TimeBaseInitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_8);

    Time_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    Time_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    Time_TimeBaseInitStructure.TIM_Period = 7200 - 1;
    Time_TimeBaseInitStructure.TIM_Prescaler = 0;
    TIM_TimeBaseInit(TIM4, &Time_TimeBaseInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OC1Init(TIM4, &TIM_OCInitStructure);
    TIM_OC3Init(TIM4, &TIM_OCInitStructure);

    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM4, ENABLE); // TIM1��ARR��Ԥװ�ؼĴ���ʹ��

    TIM_Cmd(TIM4, ENABLE);
}

void TIM_MPU6050_Config(void)
{
    TIM_TimeBaseInitTypeDef Time_TimeBaseInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    TIM_InternalClockConfig(TIM1);

    Time_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    Time_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    Time_TimeBaseInitStructure.TIM_Period = 50 - 1;
    Time_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;
    Time_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &Time_TimeBaseInitStructure);
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
    NVIC_Config();
    TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
    TIM_Cmd(TIM1, ENABLE);
}

void TIM1_UP_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM1, TIM_IT_Update))
    {
        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
        // Angle_Calcu();
        MPU6050_GetData(&Ax, &Ay, &Az, &Gx, &Gy, &Gz, &Temp);
        Pitch = MPU_Get_Pitch(Ax_offset);
        PID_CTRL();
        // Pitch = MPU_Get_Pitch(Ax_offset);
        // Roll = MPU_Get_Roll(Ay_offset);
    }
}

// void TIM4_IRQHandler(void)
// {
//     if(TIM_GetITStatus(TIM4, TIM_IT_Update))
//     {
//         printf("kk\r\n");
//     }
//     TIM_ClearITPendingBit(TIM4, TIM_IT_Update);

// }

void Delay_Ms(uint32_t ms)
{
    uint32_t i;
    SysTick_Config(72000);
    for (i = 0; i < ms; i++)
    {
        while (!((SysTick->CTRL) & (1 << 16)))
            ;
    }
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void Delay_Us(uint32_t us)
{
    uint32_t i;
    SysTick_Config(72);
    for (i = 0; i < us; i++)
    {
        while (!((SysTick->CTRL) & (1 << 16)))
            ;
    }
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}
