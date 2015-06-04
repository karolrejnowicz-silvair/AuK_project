#ifndef __MAG_ACCEL_H
#define __MAG_ACCEL_H

#include "stm32f401_discovery.h"
#include "lsm303dlhc.h"
#include "stm32f401_discovery_accelerometer.h"
#include "math.h"
#include "l3gd20.h"
#include "stm32f401_discovery_gyroscope.h"

#define ASTALA 0.000061f
#define MSTALA 0.00003967f
#define RAD_TO_DEG 57.29578f
#define DEG_TO_RAD 0.017453f

void accel_gyro_Init(uint8_t *status);
void compute_Gyro_RT_Data( float *gyroRTBias );
void getGyro(float *data, float *gyroBias);
void GyroAngle(float *angle);

extern void delay(int milisec);

#endif
