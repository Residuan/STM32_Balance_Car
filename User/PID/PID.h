#ifndef __PID_H
#define __PID_H

#include "main.h"


void PID_Init(void);

void PID_CTRL(void);
float PID_realize(float actual_val);
float Blance_PID(float actual_val);
float Speed_PID(float speed);


typedef struct
{
    float target_val;
    float err;
    float err_last;
    float Kp, Ki, Kd;
    float integral;
    float output_val;
}PID;




#endif
