/*
 * PWM.c
 *
 *  Created on: Aug 26, 2023
 *      Author: Omar Saad
 */


#include "stm32f4xx.h"
#include "PWM.h"

/*
  * Function : setup_PWM_1
  * Input : void
  * Output : void
  * Description :
  * Enable Clock for used GPIO PORTs using Static Configurationin .
  * Setup PWM signal for motor speed control
  * Configure GPIO Pins for Motor Driver
*/
void setup_PWM_1(void)
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

  // Set the initial duty cycle to 0%
  TIM1->CCR1 = 0;

  // Enable Timer 1
  TIM1->CR1 |= TIM_CR1_CEN;

  // Enable the PWM output
  TIM1->BDTR |= TIM_BDTR_MOE;
}

/*
  * Function : set_PWM_1_duty_cycle
  * Input : percentage
  * Output : void
  * Description :
  * Set PWM duty cycle for motor speed control
*/
void set_PWM_1_duty_cycle(uint8 percentage)
{
  uint16_t desired_duty_cycle = (percentage / 100.0) * (TIM1->ARR + 1);
  TIM1->CCR1 = desired_duty_cycle;
}
/*
  * Function : set_PWM_1_CCR2
  * Input : ticks
  * Output : void
  * Description :
  * set number of required ticks in  capture/compare register
*/
void set_PWM_1_CCR2(uint32 ticks)
{
  TIM2->CCR1 = ticks;
}
/*
  * Function : setup_PWM_2
  * Input : void
  * Output : void
  * Description :
  * Enable Clock for used GPIO PORTs using Static Configurationin .
  * Setup PWM signal for motor speed control
  * Configure GPIO Pins for Motor Driver
*/
void setup_PWM_2(void)
{
  // Enable the clock for Timer 2, and GPIO Port A
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

  // Configure GPIO pins for PWM output
  GPIOA->MODER |= GPIO_MODER_MODER1_1;  // Alternate function mode for TIM2_CH2 (PA1)

  GPIOA->AFR[0] |= (0x1 << ((1 - 0) * 4));  // Connect PA1 to AF1 (TIM2)

  // Configure Timer 2 for PWM generation
  TIM2->PSC = 16 - 1;  // Set the prescaler to achieve a 1 MHz clock for TIM2
  TIM2->ARR = 10000;  // Set the PWM period to 1000 cycles

  // Configure Channel 2 of Timer 2 for PWM output
  TIM2->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;  // PWM mode 1
  TIM2->CCMR1 |= TIM_CCMR1_OC2PE;  // Enable preload for CCR2
  TIM2->CCER |= TIM_CCER_CC2E;  // Enable output for Channel 2

  // Set the initial duty cycle for Channel 2 of Timer 2
  TIM2->CCR2 = 0;

  // Enable Timer 2
  TIM2->CR1 |= TIM_CR1_CEN;

  // Enable the PWM output for Timer 2
  TIM2->BDTR |= TIM_BDTR_MOE;
}
/*
  * Function : set_PWM_2_duty_cycle
  * Input : percentage
  * Output : void
  * Description :
  * Set PWM duty cycle for motor speed control
*/
void set_PWM_2_CCR2(uint32 ticks)
{
  TIM2->CCR2 = ticks;
}

/*
  * Function : setup_PWM_2
  * Input : void
  * Output : void
  * Description :
  * Enable Clock for used GPIO PORTs using Static Configurationin .
  * Setup PWM signal for motor speed control
  * Configure GPIO Pins for Motor Driver
*/
void set_PWM_2_duty_cycle(uint8 percentage)
{
  uint16_t desired_duty_cycle = (percentage / 100.0) * (TIM2->ARR + 1);
  TIM2->CCR2 = desired_duty_cycle;
}

