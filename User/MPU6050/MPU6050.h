#ifndef __MPU6050_H
#define __MPU6050_H

#include "main.h"

#define	MPU6050_SMPLRT_DIV		0x19
#define	MPU6050_CONFIG			0x1A
#define	MPU6050_GYRO_CONFIG		0x1B
#define	MPU6050_ACCEL_CONFIG	0x1C

#define	MPU6050_ACCEL_XOUT_H	0x3B
#define	MPU6050_ACCEL_XOUT_L	0x3C
#define	MPU6050_ACCEL_YOUT_H	0x3D
#define	MPU6050_ACCEL_YOUT_L	0x3E
#define	MPU6050_ACCEL_ZOUT_H	0x3F
#define	MPU6050_ACCEL_ZOUT_L	0x40
#define	MPU6050_TEMP_OUT_H		0x41
#define	MPU6050_TEMP_OUT_L		0x42
#define	MPU6050_GYRO_XOUT_H		0x43
#define	MPU6050_GYRO_XOUT_L		0x44
#define	MPU6050_GYRO_YOUT_H		0x45
#define	MPU6050_GYRO_YOUT_L		0x46
#define	MPU6050_GYRO_ZOUT_H		0x47
#define	MPU6050_GYRO_ZOUT_L		0x48

#define	MPU6050_PWR_MGMT_1		0x6B
#define	MPU6050_PWR_MGMT_2		0x6C
#define	MPU6050_WHO_AM_I		0x75

void MPU6050_Init(void);
void MPU6050_GetData(int16_t *Accx, int16_t *Accy, int16_t *Accz, int16_t *Gyrox, int16_t *Gyroy, int16_t *Gyroz, int16_t *Temp);

void MPU6050_Write(uint8_t Addr, uint8_t Data);
uint8_t MPU6050_Read(uint8_t Addr);



u8 MPU_Get_Gyroscope(short *ax,short *ay,short *az);
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az);
uint8_t MPU6050_Read_Len(u8 addr, u8 reg, u8 len, u8 *buf);
float MPU_Get_Pitch(float ax_offset);//封装Pitch角的获取
float MPU_Get_Roll(float ay_offset);//封装Roll角的获取



#endif
