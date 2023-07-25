#ifndef __I2C_H
#define __I2C_H

#include "main.h"

#define OLED_ADDRESS 0x78
#define MPU6050_ADDR    0xD0

void MPU6050_I2C_software(void);
void OLED_I2C_Hardware(void);

void I2C_W_SDA(uint8_t Bit);
uint8_t I2C_R_SDA(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendBit(uint8_t Byte);
uint8_t I2C_ReadByte(void);
void I2C_SendAck(uint8_t AckBit);
uint8_t I2C_ReadAck(void);
	
void OLED_I2C_SendCmd(uint8_t Cmd);
void OLED_I2C_SendData(uint8_t Data);




#endif
