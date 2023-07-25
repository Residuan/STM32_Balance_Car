#ifndef __MPU6050_DATA
#define __MPU6050_DATA

#include <math.h>
#include <stdlib.h>
#include "MPU6050.h"

extern float Angle_X_Final;			//解算后俯仰角
extern float Angle_Y_Final;			//解算后横滚角
extern short temperature;			//陀螺仪温度数据
extern short aacx,aacy,aacz;		//加速度传感器原始数据  angular acceleration
extern short gyrox,gyroy,gyroz;		//陀螺仪原始数据  gyroscope

extern int16_t Ax, Ay, Az, Gx, Gy, Gz, Temp;

void Angle_Calcu(void);
void Kalman_Filter_X(float Accel,float Gyro);
void Kalman_Filter_Y(float Accel,float Gyro);




#endif


