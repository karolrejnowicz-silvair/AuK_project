#include "app.h"

extern int tick;
/*
Funkcja inicjalizujaca PWM 
*/
void PWM_Init(void) {
	
	timer_init();
	pwm_init(1);
	pwm_init(2);
	pwm_init(3);
	pwm_init(4);
	
}

/*
Funkcja przeliczajaca wartosci wychodzace z akcelerometru oraz zyroskopu na kat przechylenia

*angle - wskaznik do tablicy otrzymanych katow
*gyroBias - wskaznik na tablice wartosci stalego przesuniecia zyroskopu
*/
void GetXYZangle(float *angle, float *gyroBias) {
	
	static float rawGyro[3]; //wartosci z rejestrow zyroskopu
	static float lastValue[3]; //poprzednia wartosc odczytana z rejestrow zyroskopu
	static float ACC_XYZ[3] = {0.0f, 0.0f, 0.0f}; //wartosci po przeliczeniu wartosci z rejestru accel * wartosc pojedynczej wartosci
	static float angle2[3] = {0.0f, 0.0f, 0.0f}; //kat przeychylenia w osiach XYZ
	static float currentValue[3] = {0.0f, 0.0f, 0.0f}; //wartosc obecna odczytana z rejestrow zyroskopu
	static float angleDelta[3] = {0.0f, 0.0f, 0.0f};   //roznica 
	static int16_t AccelData[3] = {0.0f, 0.0f, 0.0f};	//wartosc odczytana z rejestrow akcelerometru
	static float sinAngle, cosAngle;
	static float temp = 0.0f;

	pwm_ch_dim(700, 2); // - sluzy do deugowania zeby wiedziec czy po nacisnieciu guzika wszedlismy do funkcji
	angle2[2] = 0;
	
	while(!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)){ //jesli przycisk nie zostal wcisniety

	lastValue[2] = currentValue[2]; //wpisz obecna wartosc jako poprzednia
	
	getGyro(rawGyro, gyroBias); 		//pobierz wartosci z zyroskopu i wpisz do rawGyro[3]
	BSP_ACCELERO_GetXYZ(AccelData); //pobierz wartosci z akcelerometru i wpisz do AccelData[3]
		
	ACC_XYZ[0] = AccelData[0] * ASTALA; /* skladowa X ACC */
	ACC_XYZ[1] = AccelData[1] * ASTALA; /* skladowa Y ACC */
	ACC_XYZ[2] = AccelData[2] * ASTALA; /* skladowa Z ACC */
		
	angle2[0] = atan2f(ACC_XYZ[1], ACC_XYZ[2]) * RAD_TO_DEG;  //przelicz kat osi X
	sinAngle = sinf(angle2[0] * DEG_TO_RAD );   							//oblicz sin		
	cosAngle = cosf(angle[0] * DEG_TO_RAD );									//oblicz cosinus
		
	ACC_XYZ[2] = ACC_XYZ[1] * sinAngle + ACC_XYZ[2] * cosAngle;//przesun przeliczona wartos o kat przechylenia w osi X
	angle2[1] = atan2f(-ACC_XYZ[0],ACC_XYZ[2]) * RAD_TO_DEG; 		//policz kat osi Y
		
	currentValue[2] = rawGyro[2];																//przypisz wartosc wyciagnieta z zyroskopu jako wartosc obecna
	
	angleDelta[2] = (currentValue[2] + lastValue[2]) * 0.01f;		//przelicz roznice miedzy poprzednia i aktualna wartoscia
	
	angle2[2] += angleDelta[2];																	//kat osi Z += delta
		
	if(angle2[0] > 50) 																					//jesli kat > 50, wpisz 50
		angle2[0] = 50;
	else if (angle2[0] < -50 ) 																	//jesli kat < - 50, wpisz -50
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
	
	
	
		pwm_ch_dim((angle2[0]+50)*10 , 1); 	//ustaw wartosc w zakresie (-50, 50) do pwm
		pwm_ch_dim((angle2[1]+50)*10 , 3);	//ustaw wartosc w zakresie (-50, 50) do pwm
		pwm_ch_dim((temp+50)*10 , 4);				//ustaw wartosc w zakresie (-50, 50) do pwm
		
	delay(20); //odczekaj 20ms
	}	 
	
	tick = 0;
	delay(250);
	pwm_ch_dim(0, 2);// - sluzy do deugowania zeby wiedziec czy po nacisnieciu guzika wszedlismy do funkcji
	
}
