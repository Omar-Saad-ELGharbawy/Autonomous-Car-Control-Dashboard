/*
 * Timer.h
 *
 *  Created on: Aug 27, 2023
 *      Author: Omar Saad
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "stm32f4xx.h"

#define NULL_PTR ((void*)0)

void SysTick_Init(void);

void SysTic_setCallBack(void(*a_ptr)(void));

#endif /* TIMER_H_ */
