#include "PID.h"

PID SpeedCrl_pid;
PID Balance_pid;
PID Speed_pid;
PID Steering_pid;

int sum = 0;	 /*编码器值（PID输入）*/
int res_pwm = 0; /*PWM值（PID输出）*/

float Angle = 0;
uint16_t Balance_PWM = 0;
uint16_t Speed_PWM = 0;
uint16_t MOTOL_PWM = 0;
uint16_t MOTOR_PWM = 0;
int16_t Speed_L, Speed_R, Speed;

/************************************************************/
float Med_Angle=0;//机械中值--能使得小车真正平衡住的角度。
float
	Vertical_Kp=30,	//直立环KP、KD
	Vertical_Kd=0;
float
	Velocity_Kp=0,	//速度环KP、KI
	Velocity_Ki=0;
float 
	Turn_Kp=0;

int Vertical_out,Velocity_out,Turn_out;//直立环&速度环&转向环 的输出变量

/***************************************************************/

void PID_Init(void)
{
//	SpeedCrl_pid.target_val = 150;
//	SpeedCrl_pid.Kp = 1.4;			
//	SpeedCrl_pid.Ki = 0.81;
//	SpeedCrl_pid.Kd = 0.45;

	Balance_pid.target_val = 0;
	Balance_pid.Kp = -400;//50 35
	Balance_pid.Ki = 0;
	Balance_pid.Kd = 0;//0.5 0.07

	Speed_pid.target_val = 0;
	Speed_pid.Kp = 0;
	Speed_pid.Ki = Speed_pid.Kp / 200;
	Speed_pid.Kd = 0;

	Steering_pid.target_val = 0;
	Steering_pid.Kp = 0;
	Steering_pid.Ki = 0;
	Steering_pid.Kd = 0;
}

void PID_CTRL(void)
{
	/*读取编码器测量的速度值*/
	Speed_L = -Get_LEncoder();
	Speed_R = Get_REncoder();
	Angle = Pitch;
	/*进行PID运算，得到PWM输出值*/
	// res_pwm = PID_realize(sum);
	
	Balance_PWM = Blance_PID(Angle);
	Speed = Speed_L + Speed_R;
	Speed_PWM = Speed_PID(Speed);

	MOTOR_PWM = Balance_PWM + Speed_PWM;
	MOTOL_PWM = Balance_PWM + Speed_PWM;

//	/*根据PWM值控制电机转动*/
//	// TIM4->CCR3 = res_pwm;

	MOTO_Ctrl(MOTOL_PWM, MOTOR_PWM);

	printf("%d\n", sum);
}


float Blance_PID(float actual_val)
{

	/*PID算法实现*/
	Balance_pid.output_val = Balance_pid.Kp * (actual_val - 5) +	
					 Balance_pid.Kd * Gy;		


	/*返回当前实际值*/
	return Balance_pid.output_val;
}

float Speed_PID(float speed)
{
	static float Encoder;
	static float last_Encoder = 0;
	static float Encoder_Integral;
	
	Encoder=speed*0.1+last_Encoder*0.9;
	Encoder_Integral += Encoder;

	if(Encoder_Integral > 10000) Encoder_Integral = 10000;
	if(Encoder_Integral < -10000) Encoder_Integral = -10000;

	Speed_pid.output_val = Encoder * Speed_pid.Kp + Encoder_Integral * Speed_pid.Ki;
	last_Encoder=Encoder;
	

	return Speed_pid.output_val;
}



//float PID_realize(float actual_val)
//{

//	/*计算目标值与实际值的误差*/
//	Speed_pid.err = Speed_pid.target_val - actual_val;

//	/*积分项*/
//	Speed_pid.integral += Speed_pid.err;

//	/*PID算法实现*/
//	Speed_pid.output_val = Speed_pid.Kp * Speed_pid.err +						//Kp系数乘误差
//					Speed_pid.Ki * Speed_pid.integral +							//Ki系数乘累积误差
//					Speed_pid.Kd * (Speed_pid.err - Speed_pid.err_last);		//Kd系数乘当前与上一轮误差

//	/*误差传递*/
//	Speed_pid.err_last = Speed_pid.err;

//	/*返回当前实际值*/
//	return Speed_pid.output_val;
//}

