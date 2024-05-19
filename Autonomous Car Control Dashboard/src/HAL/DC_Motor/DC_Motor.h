/* *****************************************************************************
 * Module: DC_Motor
 *
 * File Name: DC_Motor.h
 *
 * Description: Header file for the STM32 DC_Motor driver
 *
 * Created on:  Aug 26, 2023
 * Author: Omar Saad
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "../HAL/DC_Motor/DC_Motor_Interface.h"
#include "../Libraries/Std_Types.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ANTI_CLOCKWISE 0
#define CLOCKWISE 1
#define DC_MOTOR_STOP 2


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
* Function : DC_Motor_Init
* Input : void
* Output : void
* Description :
* Enable Clock for used GPIO PORTs using Static Configurationin .
* Configure GPIO Pins for Motor Driver
*/
void DC_Motor_Init(void);

/*
* Function : DC_Motor_SetSpeed
* Input : speed
* Output : void
* Description :
* Set DC Motor Speed by PWM
*/
void DC_Motor_SetSpeed(uint8 speed);

/*
* Function : DC_Motor_SetDirection
* Input : direction
* Output : void
* Description :
* Set DC Motor Direction (Clockwise or Anti-Clockwise)
*/
void DC_Motor_SetDirection(uint8 direction);

/*
* Function : DC_Motor_Stop
* Input : void
* Output : void
* Description :
* Stop DC Motor
*/
void DC_Motor_Stop(void);

#endif /* DC_MOTOR_H_ */
