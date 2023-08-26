/*
 * PWM.c
 *
 *  Created on: Aug 26, 2023
 *      Author: Omar Saad
 */


#include "stm32f4xx.h"

#include "PWM.h"

void setup_PWM(void)
{
  // Enable the clock for Timer 1 and GPIO Port A
  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

  // Configure GPIO pins for PWM output
  GPIOA->MODER |= GPIO_MODER_MODER8_1;  // Alternate function mode
  GPIOA->AFR[1] |= (0x1 << ((8 - 8) * 4));  // Connect to AF1 (TIM1) on pin PA8

  // Configure Timer 1 for PWM generation
  TIM1->PSC = 16 - 1;  // Set the prescaler to achieve a 1 MHz clock
  TIM1->ARR = 1000 - 1;  // Set the PWM period to 1000 cycles

  // Configure Channel 1 of Timer 1 for PWM output
  TIM1->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;  // PWM mode 1
  TIM1->CCMR1 |= TIM_CCMR1_OC1PE;  // Enable preload for CCR1
  TIM1->CCER |= TIM_CCER_CC1E;  // Enable output for Channel 1

  // Set the initial duty cycle to 50%
  TIM1->CCR1 = 1000-1;

  // Enable Timer 1
  TIM1->CR1 |= TIM_CR1_CEN;

  // Enable the PWM output
  TIM1->BDTR |= TIM_BDTR_MOE;
}

void set_PWM_duty_cycle(uint8 percentage)
{
  uint16_t desired_duty_cycle = (percentage / 100.0) * (TIM1->ARR + 1);
  TIM1->CCR1 = desired_duty_cycle;
}
