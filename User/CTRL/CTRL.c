#include "CTRL.h"

void Ctrl_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

int myabs(int p)
{
	int temp;
	if (p < 0)
		temp = -p;
	else
		temp = p;
	return temp;
}

void MOTO_Ctrl(uint16_t MOTO_L, uint16_t MOTO_R)
{
	//    if ((MOTO_L > 70) || (MOTO_R > 70))
	//    {
//	if (MOTO_L > 0)
//	{
//		MOTO_L1(1);
//		MOTO_L2(0);
//	}
//	else
//	{
//		MOTO_L1(0);
//		MOTO_L2(1);
//	}
//	MOTO_L_PWM = myabs(MOTO_L);

//	if (MOTO_R > 0)
//	{
//		MOTO_R1(0);
//		MOTO_R2(1);
//	}
//	else
//	{
//		MOTO_R1(1);
//		MOTO_R2(0);
//	}
//	MOTO_R_PWM = myabs(MOTO_R);
	       if (Pitch < 0)
	       {
	           MOTO_L1(0);
	           MOTO_L2(1);
	           MOTO_R1(0);
	           MOTO_R2(1);
	
	           MOTO_L_PWM = myabs(MOTO_L);
	           MOTO_R_PWM = myabs(MOTO_R);
	       }
	       if (Pitch > 0)
	       {

	           MOTO_L1(1);
	           MOTO_L2(0);
	           MOTO_R1(1);
	           MOTO_R2(0);
	           MOTO_L_PWM = myabs(MOTO_L);
	           MOTO_R_PWM = myabs(MOTO_R);
	       }
	//				if (((Pitch > 90) && ((MOTO_L > 900) || (MOTO_R > 900))) || ((Pitch < 90) && ((MOTO_L > 900) || (MOTO_R > 900))))
	//				{
	//						MOTO_L_PWM = 0;
	//        	  MOTO_R_PWM = 0;
	//				}
	//        if (Pitch == 0)
	//        {
	//            MOTO_L1(0);
	//            MOTO_L2(0);
	//            MOTO_R1(0);
	//            MOTO_R2(0);
	//            MOTO_L_PWM = 0;
	//            MOTO_R_PWM = 0;
	//        }
	//    }
	//    else
	//    {
	//        MOTO_L_PWM = 0;
	//        MOTO_R_PWM = 0;
	//    }
}
