/*
 ============================================================================
 Name        : TIMfreq_calculate.c
 Author      : AAA
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define PCLK1 32000000
#define LED_PWM_FREQ (200)	// Hz

static int duty_percent = 50;	// in %

int main(void)
{
	uint32_t APBfreq = PCLK1;// HAL_RCC_GetPCLK1Freq();
    APBfreq *= 1;//(RCC->CFGR & RCC_CFGR_PPRE1) == 0 ? 1 : 2;

	uint32_t Prescaler = 0, TIMfreq = APBfreq;
    while ((TIMfreq / LED_PWM_FREQ) > 65535) {
		Prescaler += 2;
		TIMfreq = APBfreq / Prescaler;
    }
    if (Prescaler > 0)
		Prescaler -= 1;
	uint32_t Period = (TIMfreq / LED_PWM_FREQ) - 1;

	printf("Base freq: %d\nSet freq: %d\nPrescaler: %d\nTIM freq: %d\nPeriod (ARR): %d\n", PCLK1, LED_PWM_FREQ, Prescaler, TIMfreq, Period);


	uint32_t ARR_reg = Period;
	uint32_t full = ARR_reg;//__HAL_TIM_GET_AUTORELOAD(&htim3);
	//__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, (duty_percent * full / 100));
	uint32_t CCR = (duty_percent * full / 100);
	printf("Duty: %d\nCCR value: %d\n", duty_percent, CCR);

	return EXIT_SUCCESS;
}

