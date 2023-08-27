/*
 * Timer.c
 *
 *  Created on: Aug 27, 2023
 *      Author: Omar Saad
 */

#include "Systick_Timer.h"
#include "stm32f4xx.h"

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;


void SysTick_Init(void)
{
  // Set SysTick interrupt priority
  NVIC_SetPriority(SysTick_IRQn, 0);  // Set priority level 0 or adjust as needed

  // Enable SysTick interrupt
  NVIC_EnableIRQ(SysTick_IRQn);

  // Configure SysTick
  SysTick->LOAD = SystemCoreClock - 1;  // Set the reload value for 1 second interrupt
//  SysTick->LOAD = 1000000 -1;  // Set the reload value for 1 second interrupt
  SysTick->VAL = 0;                     // Clear the current value
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void SysTic_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;

}


void SysTick_Handler(void)
{
  // Your code to be executed each second
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)();
	}

}

