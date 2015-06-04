#include "mag_accel.h"

extern int tick;
extern uint8_t button_flag;

void accel_gyro_Init(uint8_t *status) {
	
	status[0] = BSP_ACCELERO_Init();
	status[1] = BSP_GYRO_Init();
}

void compute_Gyro_RT_Data( float *gyroRTBias ) {
	
	uint8_t axis;
	uint16_t samples;
	float rawTable[3] = { 0.0f, 0.0f, 0.0f };
	float gyroSum[3] = { 0.0f, 0.0f, 0.0f };
	 
	
	for ( samples = 0; samples < 2000; samples++) {
		
		BSP_GYRO_GetXYZ(rawTable);
		
		gyroSum[0] += rawTable[0];
		gyroSum[1] += rawTable[1];
		gyroSum[2] += rawTable[2];
		delay(1);
	}
	
	for (axis = 0; axis < 3; axis++) {
		
		gyroRTBias[axis] = gyroSum[axis] / 2000.0f;
		
	}
}

void getGyro(float *data, float *gyroBias) {
	
	float rawTable[3];
	BSP_GYRO_GetXYZ(rawTable);
	data[0] = ( rawTable[0] - gyroBias[0] );
	data[1] = ( rawTable[1] - gyroBias[1] );
	data[2] = ( rawTable[2] - gyroBias[2] );
}


void GyroAngle(float *angle) {
	
	static float gyroBias[3];
	static float rawGyro[3];
	static float lastValue[3];
	static float ACC_XYZ[3] = {0.0f, 0.0f, 0.0f};
	static float angle2[3] = {0.0f, 0.0f, 0.0f};
	static float currentValue[3] = {0.0f, 0.0f, 0.0f};
	static float angleDelta[3] = {0.0f, 0.0f, 0.0f};
	static int16_t Data[3] = {0.0f, 0.0f, 0.0f};
	static float sinAngle, cosAngle;
	//uint32_t time[2] = {0, 0};
	static float temp = 0.0f;
	
	compute_Gyro_RT_Data(gyroBias);
	timer_init();
	pwm_ch1_init();
	//pwm_ch2_init();
	pwm_ch3_init();
	pwm_ch4_init();
	
	//angle2[0] = angle2[1] = angle2[2] = 0;
	while(!button_flag){

	//lastValue[0] = currentValue[0];
	//lastValue[1] = currentValue[1];
	lastValue[2] = currentValue[2];
	
	getGyro(rawGyro, gyroBias);
	BSP_ACCELERO_GetXYZ(Data);
		
		ACC_XYZ[0] = Data[0] * ASTALA; /* skladowa X ACC */
		ACC_XYZ[1] = Data[1] * ASTALA; /* skladowa Y ACC */
		ACC_XYZ[2] = Data[2] * ASTALA; /* skladowa Z ACC */
		
		angle2[0] = atan2f(ACC_XYZ[1], ACC_XYZ[2]) * RAD_TO_DEG;
		sinAngle = sinf(angle2[0] * DEG_TO_RAD ); 
		cosAngle = cosf(angle[0] * DEG_TO_RAD );
		
		ACC_XYZ[2] = ACC_XYZ[1] * sinAngle + ACC_XYZ[2] * cosAngle;
		angle2[1] = atan2f(-ACC_XYZ[0],ACC_XYZ[2]) * RAD_TO_DEG;
		
	//currentValue[0] = rawGyro[0];
	//currentValue[1] = rawGyro[1];
	currentValue[2] = rawGyro[2];
	
	//angleDelta[0] = (currentValue[0] + lastValue[0]) * 0.01f;
	//angleDelta[1] = (currentValue[1] + lastValue[1]) * 0.01f;
	angleDelta[2] = (currentValue[2] + lastValue[2]) * 0.01f;
	
	//angle2[0] += angleDelta[0];
	//angle2[1] += angleDelta[1];
	angle2[2] += angleDelta[2];
	
	if(angle2[0] > 50)
		angle2[0] = 50;
	else if (angle2[0] < -50 ) 
		angle2[0] = -50;
	
	if(angle2[1] > 50)
		angle2[1] = 50;
	else if (angle2[1] < -50 ) 
		angle2[1] = -50;
	
	temp = angle2[2];
	if(temp > 50)
		temp = 50;
	else if (temp < -50 ) 
		temp = -50;
	
	
	
		pwm_ch1_dim((angle2[0]+50)*10 , 1);	
		pwm_ch1_dim((angle2[1]+50)*10 , 3);
		pwm_ch1_dim((temp+50)*10 , 4);
		
	delay(20);
	}	
	button_flag = 0;
}
