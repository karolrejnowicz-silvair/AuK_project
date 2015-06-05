#include "mag_accel.h"

extern int tick;

/*
Funkcja inicjalizuje akcelerometr i zyroskop, 
wywoluje funkcje obliczajaca stale przesuniecie zyroskopu

*status - wskaznik na tablice statusu inicjalizacji 0 - OK, 1 - nie OK
*gyroRTBias - wskaznik na tablice wartosci stalego przesuniecia zyroskopu 
							na kazdej osi
*/
void accel_gyro_Init(uint8_t *status, float *gyroError) {

	
	status[0] = BSP_ACCELERO_Init(); 	
	status[1] = BSP_GYRO_Init();				
	compute_Gyro_RT_Data( gyroError );	
	

}

/*
Funkcja liczy stale przesuniecie wartosci zwracanych przez zyroskop w trzech osiach

*gyroRTBias - wskaznik na tablice wartosci stalego przesuniecia zyroskopu 
							na kazdej osi
*/
void compute_Gyro_RT_Data( float *gyroError ) { 
	
	uint8_t axis;
	uint16_t samples;
	float rawTable[3] = { 0.0f, 0.0f, 0.0f };
	float gyroSum[3] = { 0.0f, 0.0f, 0.0f };
	 
	tick = 0;
	for ( samples = 0; samples < 2000; samples++) {
		
		BSP_GYRO_GetXYZ(rawTable);
		
		gyroSum[0] += rawTable[0];
		gyroSum[1] += rawTable[1];
		gyroSum[2] += rawTable[2];
		delay(1);
	}
	
	for (axis = 0; axis < 3; axis++) {
		
		gyroError[axis] = gyroSum[axis] / 2000.0f;
		
	}
}

/*
Funkcja podaje wartosci zwracane przez zyroskop i odejmuje od nich stale przesuniecie

*data - wartosci przesuniete, gotowe do obrobki
*/
void getGyro(float *data, float *gyroBias) { 
	
	float rawTable[3];
	BSP_GYRO_GetXYZ(rawTable);
	data[0] = ( rawTable[0] - gyroBias[0] );
	data[1] = ( rawTable[1] - gyroBias[1] );
	data[2] = ( rawTable[2] - gyroBias[2] );
}



