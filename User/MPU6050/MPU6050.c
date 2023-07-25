#include "MPU6050.h"

static float rad2deg = 57.29578;
static int gx, gy;
static int ax, ay, az;
static float pitch, roll;

static float angle1, angle2;
static float ex_gyro = 0, ey_gyro = 0;
static int dt = 0.001;
static float ki = 0.01;

void MPU6050_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE); // 使能相应接口的时钟，以及RCC_APB2Periph_AFIO
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);                    // 禁用JTAG

    MPU6050_I2C_software();

    MPU6050_Write(MPU6050_PWR_MGMT_1, 0x01);
    MPU6050_Write(MPU6050_PWR_MGMT_2, 0x00);
    MPU6050_Write(MPU6050_SMPLRT_DIV, 0x09);
    MPU6050_Write(MPU6050_CONFIG, 0x06);
    MPU6050_Write(MPU6050_GYRO_CONFIG, 0x18);
    MPU6050_Write(MPU6050_ACCEL_CONFIG, 0x18);
}

void MPU6050_GetData(int16_t *Accx, int16_t *Accy, int16_t *Accz, int16_t *Gyrox, int16_t *Gyroy, int16_t *Gyroz, int16_t *Temp)
{
    uint8_t DataH, DataL;
    DataH = MPU6050_Read(MPU6050_ACCEL_XOUT_H);
    DataL = MPU6050_Read(MPU6050_ACCEL_XOUT_L);
    *Accx = (DataH << 8) | DataL;

    DataH = MPU6050_Read(MPU6050_ACCEL_YOUT_H);
    DataL = MPU6050_Read(MPU6050_ACCEL_YOUT_L);
    *Accy = (DataH << 8) | DataL;

    DataH = MPU6050_Read(MPU6050_ACCEL_ZOUT_H);
    DataL = MPU6050_Read(MPU6050_ACCEL_ZOUT_L);
    *Accz = (DataH << 8) | DataL;

    DataH = MPU6050_Read(MPU6050_GYRO_XOUT_H);
    DataL = MPU6050_Read(MPU6050_GYRO_XOUT_L);
    *Gyrox = (DataH << 8) | DataL;

    DataH = MPU6050_Read(MPU6050_GYRO_YOUT_H);
    DataL = MPU6050_Read(MPU6050_GYRO_YOUT_L);
    *Gyroy = (DataH << 8) | DataL;

    DataH = MPU6050_Read(MPU6050_GYRO_ZOUT_H);
    DataL = MPU6050_Read(MPU6050_GYRO_ZOUT_L);
    *Gyroz = (DataH << 8) | DataL;

    DataH = MPU6050_Read(MPU6050_TEMP_OUT_H);
    DataL = MPU6050_Read(MPU6050_TEMP_OUT_L);
    *Temp = (DataH << 8) | DataL;
}

void MPU6050_Write(uint8_t Addr, uint8_t Data)
{
    I2C_Start();
    I2C_SendBit(MPU6050_ADDR);
    I2C_ReadAck();
    I2C_SendBit(Addr);
    I2C_ReadAck();
    I2C_SendBit(Data);
    I2C_ReadAck();
    I2C_Stop();
}

uint8_t MPU6050_Read(uint8_t Addr)
{
    uint8_t Data = 0x00;
    I2C_Start();
    I2C_SendBit(MPU6050_ADDR);
    I2C_ReadAck();
    I2C_SendBit(Addr);
    I2C_ReadAck();
    I2C_Start();
    I2C_SendBit(MPU6050_ADDR | 0x01);
    I2C_ReadAck();
    Data = I2C_ReadByte();
    I2C_SendAck(1);
    I2C_Stop();
    return Data;
}

uint8_t MPU6050_Read_Len(u8 addr, u8 reg, u8 len, u8 *buf)
{

    I2C_Start();
    I2C_SendBit(MPU6050_ADDR);
    if (I2C_ReadAck()) // 等待应答
    {
        I2C_Stop();
        return 1;
    }
    I2C_SendBit(reg);
    I2C_ReadAck();

    I2C_Start();
    I2C_SendBit(MPU6050_ADDR | 0x01);
    I2C_ReadAck();

    while (len)
    {
        if (len == 1)
        {
            *buf = I2C_ReadByte(); // 读数据,发送nACK
            I2C_SendAck(1);
        }
        else
        {
            *buf = I2C_ReadByte(); // 读数据,发送ACK
            I2C_SendAck(0);
        }
        len--;
        buf++;
    }
    I2C_Stop();
    return 0;
}

u8 MPU_Get_Accelerometer(short *ax, short *ay, short *az)
{
    u8 buf[6], res;
    res = MPU6050_Read_Len(MPU6050_ADDR, MPU6050_ACCEL_XOUT_H, 6, buf);
    if (res == 0)
    {
        *ax = ((u16)buf[0] << 8) | buf[1];
        *ay = ((u16)buf[2] << 8) | buf[3];
        *az = ((u16)buf[4] << 8) | buf[5];
    }
    return res;
}

u8 MPU_Get_Gyroscope(short *ax, short *ay, short *az)
{
    u8 buf[6], res;
    res = MPU6050_Read_Len(MPU6050_ADDR, MPU6050_GYRO_XOUT_H, 6, buf);
    if (res == 0)
    {
        *ax = ((u16)buf[0] << 8) | buf[1];
        *ay = ((u16)buf[2] << 8) | buf[3];
        *az = ((u16)buf[4] << 8) | buf[5];
    }
    return res;
}

float MPU_Get_Pitch(float ax_offset) // 封装Pitch角的获取
{
    // MPU6050_GetData(&Ax, &Ay, &Az, &Gx, &Gy, &Gz, &Temp);
    gx = Gx;
    gy = Gy;
    // gz = Gz;
    ax = Ax;
    ay = Ay;
    az = Az;

    angle1 = atan2((ax - ax_offset), az) * rad2deg; // 互补滤波可用，但开机偏移2度
    ex_gyro = gx * dt / 1000.f;
    pitch = ki * (ex_gyro + pitch) + (1 - ki) * angle1;
    return pitch;
}

float MPU_Get_Roll(float ay_offset) // 封装Roll角的获取
{
    // MPU6050_GetData(&Ax, &Ay, &Az, &Gx, &Gy, &Gz, &Temp);
    gx = Gx;
    gy = Gy;
    // gz = Gz;
    ax = Ax;
    ay = Ay;
    az = Az;

    angle2 = atan2(ay - ay_offset, az) * rad2deg; // 互补滤波可用，正常使用
    ey_gyro = gy * dt / 1000.f;
    roll = ki * (ey_gyro + roll) + (1 - ki) * angle2;
    return roll;
}
