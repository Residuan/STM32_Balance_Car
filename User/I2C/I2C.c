#include "I2C.h"
uint16_t TimeOut;

void MPU6050_I2C_software(void)
{
    GPIO_InitTypeDef    GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_3 | GPIO_Pin_4);
}

void OLED_I2C_Hardware(void)
{
    GPIO_InitTypeDef    GPIO_InitStructure;
    I2C_InitTypeDef     I2C_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // I2C_StructInit(&I2C_InitStructure);
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = 400000;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_OwnAddress1 = 0x00;
    I2C_Init(I2C2, &I2C_InitStructure);
    I2C_Cmd(I2C2, ENABLE);

}



void OLED_I2C_Haedwaer_Send(uint8_t addr, uint8_t Data)
{
    I2C_GenerateSTART(I2C2, ENABLE);
    while (! I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C2, OLED_ADDRESS, I2C_Direction_Transmitter);
    while(! I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    I2C_SendData(I2C2, addr);
    while(! I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING));
    I2C_SendData(I2C2, Data);
    while(! I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    I2C_GenerateSTOP(I2C2, ENABLE);
}

void OLED_I2C_SendCmd(uint8_t Cmd)
{
    OLED_I2C_Haedwaer_Send(0x00, Cmd);
}

void OLED_I2C_SendData(uint8_t Data)
{
    OLED_I2C_Haedwaer_Send(0x40, Data);
}



void I2C_W_SCL(uint8_t Bit)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_3, (BitAction)Bit);
    // Delay_Us(10);
}

void I2C_W_SDA(uint8_t Bit)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_4, (BitAction)Bit);
    // Delay_Us(10);
}

uint8_t I2C_R_SDA(void)
{
    uint8_t Bit;
    Bit = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4);
    // Delay_Us(10);
    return Bit;
}

void I2C_Start(void)
{
    I2C_W_SDA(1);
    I2C_W_SCL(1);
    I2C_W_SDA(0);
    I2C_W_SCL(0);
}

void I2C_Stop(void)
{
    I2C_W_SDA(0);
    I2C_W_SCL(1);
    I2C_W_SDA(1);
}

void I2C_SendBit(uint8_t Byte)
{
    uint8_t i;
    for (i = 0; i < 8; i++)
    {
        I2C_W_SDA(Byte & (0x80 >> i));
        I2C_W_SCL(1);
        I2C_W_SCL(0);
    }
}

uint8_t I2C_ReadByte(void)
{
    uint8_t i, byte = 0x00;
    I2C_W_SDA(1);
    for (i = 0; i < 8; i++)
    {
        I2C_W_SCL(1);
        if (I2C_R_SDA() == 1)
        {   
            byte |= (0x80 >> i);
        }
        I2C_W_SCL(0);
    }
    return byte;
}

void I2C_SendAck(uint8_t AckBit)
{
    I2C_W_SDA(AckBit);
    I2C_W_SCL(1);
    I2C_W_SCL(0);
}

uint8_t I2C_ReadAck(void)
{
    uint8_t AckBit;
    I2C_W_SDA(1);
    I2C_W_SCL(1);
    AckBit = I2C_R_SDA();
    I2C_W_SCL(0);
    return AckBit;
}





