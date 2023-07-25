#ifndef __MPU6050_DATA
#define __MPU6050_DATA

#include <math.h>
#include <stdlib.h>
#include "MPU6050.h"

extern float Angle_X_Final;			//���������
extern float Angle_Y_Final;			//���������
extern short temperature;			//�������¶�����
extern short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����  angular acceleration
extern short gyrox,gyroy,gyroz;		//������ԭʼ����  gyroscope

extern int16_t Ax, Ay, Az, Gx, Gy, Gz, Temp;

void Angle_Calcu(void);
void Kalman_Filter_X(float Accel,float Gyro);
void Kalman_Filter_Y(float Accel,float Gyro);




#endif


