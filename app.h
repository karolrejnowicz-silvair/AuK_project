#ifndef __APP_H
#define __APP_H

#include "math.h"
#include "tim_pwm.h"
#include "mag_accel.h"

#define ASTALA 0.000061f // dla dokladnosci 2g, pojedyncza wartosc rejestru = ASTALA
#define RAD_TO_DEG 57.29578f
#define DEG_TO_RAD 0.017453f

extern uint8_t button_flag;


void GetXYZangle(float *angle, float *gyroBias);
void PWM_Init(void);
	
#endif 
