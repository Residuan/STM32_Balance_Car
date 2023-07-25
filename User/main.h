#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f10x.h"
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "CTRL.h"
#include "ENCODE.h"
#include "TIM.h"
#include "I2C.h"
#include "MPU6050.h"
#include "USART.h"
#include "PID.h"
#include "OLED.h"
#include "MPU6050_DATA.h"

extern int16_t Ax, Ay, Az, Gx, Gy, Gz, Temp;
extern float Ax_offset, Ay_offset, Az_offset, Gx_offset, Gy_offset, Gz_offset;
extern float Pitch, Roll, Yaw; // Æ«º½½Ç£¬¸©Ñö½Ç£¬·­¹ö½Ç
extern int16_t Speed_L, Speed_R, Speed;



#endif

