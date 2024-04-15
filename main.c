/*
 * PRELAB_5.c
 *
 * Created: 14/04/2024 12:12:48
 * Author : pablo
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "PWM0/PWM0.h"
#include "ADC/ADC.h"
#include "PWM1/PWM1.h"
#define ADC_MAX 255
#define DUTY_MIN 0
#define DUTY_MAX 40

uint8_t dutyCycle = 0;
uint8_t dutyCycle1 = 0;
uint8_t dutyCycle1H = 0;
uint8_t dutyCycle1L = 0;

void setup(void){
	cli();
	UCSR0B = 0;
	sei();
	initADC();
}

uint8_t mapADCtoDC(uint8_t adcValue){
	return(uint8_t)(((float)adcValue / ADC_MAX) * (DUTY_MAX - DUTY_MIN) + DUTY_MIN);
}

int main(void)
{
	setup();
	
	initPWM0FastA(no_invertido, 1024);
	initPWM1Fast_16bit(no_invertido, 8);
    while (1) 
    {
		dutyCycle1 = (7.84*ADCH)+2000;
		dutyCycle1L = (dutyCycle1 & 0x0F);
		dutyCycle1L = (dutyCycle1 >> 4);
		dutyCycle = mapADCtoDC(ADCH);
		ADCSRA |= (1<<ADSC);
		updateDutyCicleA(dutyCycle);
		updateDutyCycle1A(dutyCycle1H, dutyCycle1L);
    }
}

ISR(ADC_vect){
	
	ADCSRA |=(1<<ADIF);
}
