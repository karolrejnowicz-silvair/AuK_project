#ifndef __MAG_ACCEL_H
#define __MAG_ACCEL_H

#include "stm32f401_discovery_accelerometer.h"
#include "stm32f401_discovery_gyroscope.h"


void accel_gyro_Init(uint8_t *status, float *gyroError);
void compute_Gyro_RT_Data( float *gyroError );
void getGyro(float *data, float *gyroBias);

extern void delay(int milisec);

#endif
