#include "main.h"
#include "gai_mpu6050.h"

// #define Kp 100.0f    // ��������֧�������������ٶȼ�/��ǿ��
// #define Ki 0.002f    // ��������֧���ʵ�������ƫ�����ν�
// #define halfT 0.001f // �������ڵ�һ��

void OLED_ShowMPU6050(void);

// void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az);
// float yijiehubu(float angle_m, float gyro_m); // �ɼ������ĽǶȺͽǼ��ٶ�

uint8_t time = 0;

uint8_t data;
int16_t Ax, Ay, Az, Gx, Gy, Gz, Temp;

float Ax_offset, Ay_offset, Az_offset, Gx_offset, Gy_offset, Gz_offset;
// ��Ԫ����
float Pitch, Roll, Yaw; // ƫ���ǣ������ǣ�������

// float nowtemp;

// float q0 = 1, q1 = 0, q2 = 0, q3 = 0;  // ��Ԫ����Ԫ�أ�������Ʒ���
// float exInt = 0, eyInt = 0, ezInt = 0; // ��������С�������

// һ�׻����˲�
// float K1 = 0.1;   // �Լ��ٶȼ�ȡֵ��Ȩ��
// float dt = 0.001; // ע�⣺dt��ȡֵΪ�˲�������ʱ��
// float angle;
// float angle_ax, gy;

void MPU6050_OffSet(void)
{
    uint16_t i;
    for (i = 0; i < 200; i++)
    {
        MPU6050_GetData(&Ax, &Ay, &Az, &Gx, &Gy, &Gz, &Temp);
        Ax_offset += Ax;
        Ay_offset += Ay;
        Az_offset += Az;
        Gx_offset += Gx;
        Gy_offset += Gy;
        Gz_offset += Gz;
    }
    Ax_offset /= 2000;
    Ay_offset /= 2000;
    Az_offset /= 2000;
    Gx_offset /= 2000;
    Gy_offset /= 2000;
    Gz_offset /= 2000;
}

void All_Init(void)
{
    MPU6050_Init();

    OLED_Init();
    USART_Config(115200);

    Ctrl_Init();
    PWM_Config();
    ENCODE_Config();
    PID_Init();
    printf("��ʼ����� >.O\r\n");

    TIM_MPU6050_Config();
    OLED_ShowString(1, 1, "All Init is OK!");
    //    MPU6050_OffSet();
    Delay_Ms(1000);
}

int main(void)
{
    All_Init();

    data = MPU6050_Read(MPU6050_WHO_AM_I);

    printf("%x\n", data);

    OLED_ShowString(1, 1, "    Pitch   Roll ");

    while (1)
    {

        // MPU6050_GetData(&Ax, &Ay, &Az, &Gx, &Gy, &Gz, &Temp);

        // printf("%d\r\n", Get_LEncoder());
        // IMUupdate(Gx, Gy, Gz, Ax, Ay, Az); // ��Ԫ����

        // angle_ax = atan(Ax / Az) * 57.3; // ���ٶȵõ��ĽǶ�
        // gy = (float)Gy / 7510.0;     // �����ǵõ��Ľ��ٶ�
        // Pitch = yijiehubu(angle_ax, gy);

        //        printf("L:%d, R:%d\r\n", Get_LEncoder(), Get_REncoder());

        printf("Ax:%d, Ay:%d, Az:%d, Gx:%d, Gy:%d, Gz:%d\n", Ax, Ay, Az, Gx, Gy, Gz);
        //        Pitch = MPU_Get_Pitch(Ax_offset);
        Roll = MPU_Get_Roll(Ay_offset);

        //        PID_CTRL();

        // printf("Pitch:%.4f, Roll:%.4f\n", Pitch, Roll);
        OLED_ShowMPU6050();

        //        Delay_Ms(10);
    }
}

void OLED_ShowMPU6050(void)
{
    // OLED_ShowString(1, 1, "    Acc   Gyro ");

    // OLED_ShowString(2, 1, "X:");
    // OLED_ShowString(3, 1, "Y:");
    // OLED_ShowString(4, 1, "Z:");
    // OLED_ShowSignedNum(2, 4, Ax, 4);
    // OLED_ShowSignedNum(3, 4, Ay, 4);
    // OLED_ShowSignedNum(4, 4, Az, 4);

    // OLED_ShowSignedNum(2, 10, Gx, 4);
    // OLED_ShowSignedNum(3, 10, Gy, 4);
    // OLED_ShowSignedNum(4, 10, Gz, 4);

    OLED_ShowSignedNum(2, 4, Pitch, 4);
    OLED_ShowSignedNum(2, 10, Roll, 4);

    OLED_ShowSignedNum(3, 1, Speed_L, 4);
    OLED_ShowSignedNum(4, 1, Speed_R, 4);
}

// void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az) // ��Ԫ����
// {
//     float norm;
//     float vx, vy, vz;
//     float ex, ey, ez;

//     // ����������
//     norm = sqrt(ax * ax + ay * ay + az * az);
//     ax = ax / norm; // ��λ��
//     ay = ay / norm;
//     az = az / norm;

//     // ���Ʒ��������
//     vx = 2 * (q1 * q3 - q0 * q2);
//     vy = 2 * (q0 * q1 + q2 * q3);
//     vz = q0 * q0 - q1 * q1 - q2 * q2 + q3 * q3;

//     // ���������ͷ��򴫸��������ο�����֮��Ľ���˻����ܺ�
//     ex = (ay * vz - az * vy);
//     ey = (az * vx - ax * vz);
//     ez = (ax * vy - ay * vx);

//     // ������������������
//     exInt = exInt + ex * Ki;
//     eyInt = eyInt + ey * Ki;
//     ezInt = ezInt + ez * Ki;

//     // ������������ǲ���
//     gx = gx + Kp * ex + exInt;
//     gy = gy + Kp * ey + eyInt;
//     gz = gz + Kp * ez + ezInt;

//     // ������Ԫ���ʺ�������
//     q0 = q0 + (-q1 * gx - q2 * gy - q3 * gz) * halfT;
//     q1 = q1 + (q0 * gx + q2 * gz - q3 * gy) * halfT;
//     q2 = q2 + (q0 * gy - q1 * gz + q3 * gx) * halfT;
//     q3 = q3 + (q0 * gz + q1 * gy - q2 * gx) * halfT;

//     // ��������Ԫ
//     norm = sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
//     q0 = q0 / norm;
//     q1 = q1 / norm;
//     q2 = q2 / norm;
//     q3 = q3 / norm;

//     Pitch = asin(-2 * q1 * q3 + 2 * q0 * q2) * 57.3;                                // pitch ,ת��Ϊ����
//     Roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2 * q2 + 1) * 57.3; // rollv
//                                                                                     // Yaw = atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.3;                //�˴�û�м�ֵ��ע��
// }

// float yijiehubu(float angle_m, float gyro_m) // �ɼ������ĽǶȺͽǼ��ٶ�
// {
//     angle = K1 * angle_m + (1 - K1) * (angle + gyro_m * dt);
//     return angle;
// }

// //һ�׻����˲�
// float K1 =0.1; // �Լ��ٶȼ�ȡֵ��Ȩ��
// float dt=0.001;//ע�⣺dt��ȡֵΪ�˲�������ʱ��
// float angle_P,angle_R;

// float yijiehubu_P(float angle_m, float gyro_m)//�ɼ������ĽǶȺͽǼ��ٶ�
// {
//      angle_P = K1 * angle_m + (1-K1) * (angle_P + gyro_m * dt);
//          return angle_P;
// }

// float yijiehubu_R(float angle_m, float gyro_m)//�ɼ������ĽǶȺͽǼ��ٶ�
// {
//      angle_R = K1 * angle_m + (1-K1) * (angle_R + gyro_m * dt);
//          return angle_R;
// }
