/* *****************************************************************************
 * Module: DC_Motor
 *
 * File Name: DC_Motor.c
 *
 * Description: Source file for the STM32 DC_Motor driver
 *
 * Created on:  Aug 26, 2023
 * Author: Omar Saad
 *
 *******************************************************************************/

#include "../HAL/DC_Motor/DC_Motor.h"

#include "../Libraries/Std_Types.h"
#include "../Libraries/Utils.h"
#include "../MCAL/Gpio/Gpio.h"
#include "../MCAL/Rcc/Rcc.h"
#include "../../MCAL/PWM/PWM.h"


/*
* Function : DC_Motor_Init
* Input : void
* Output : void
* Description :
* Enable Clock for used GPIO PORTs using Static Configurationin .
* Setup PWM signal for motor speed control
* Configure GPIO Pins for Motor Driver
*/
void DC_Motor_Init(void){
    Rcc_Enable(DC_MOTOR_PORT);
    setup_PWM_1();
    /* Configure Output pins for DC Motor */
	Gpio_ConfigPin(DC_MOTOR_PORT, DC_MOTOR_INPUT_1, GPIO_OUTPUT, GPIO_PUSH_PULL, NOT_INPUT);
	Gpio_WritePinValue(DC_MOTOR_PORT, DC_MOTOR_INPUT_1, LOW);
	Gpio_ConfigPin(DC_MOTOR_PORT, DC_MOTOR_INPUT_2, GPIO_OUTPUT, GPIO_PUSH_PULL, NOT_INPUT);
	Gpio_WritePinValue(DC_MOTOR_PORT, DC_MOTOR_INPUT_1, LOW);
}
/*
* Function : DC_Motor_SetSpeed
* Input : speed
* Output : void
* Description :
* Set DC Motor Speed by PWM
*/
void DC_Motor_SetSpeed(uint8 speed){
    if(speed > 100){
        speed = 100;
    }
    set_PWM_1_duty_cycle(speed);
}
/*
* Function : DC_Motor_SetDirection
* Input : direction
* Output : void
* Description :
* Set DC Motor Direction (Clockwise or Anti-Clockwise)
*/
void DC_Motor_SetDirection(uint8 direction){
    switch(direction){
        case ANTI_CLOCKWISE:
            /* Anti Clockwise*/
            Gpio_WritePinValue(DC_MOTOR_PORT, DC_MOTOR_INPUT_1, HIGH);
            Gpio_WritePinValue(DC_MOTOR_PORT, DC_MOTOR_INPUT_2, LOW);
            break;
        case CLOCKWISE:
            /* Clockwise*/
            Gpio_WritePinValue(DC_MOTOR_PORT, DC_MOTOR_INPUT_1, LOW);
            Gpio_WritePinValue(DC_MOTOR_PORT, DC_MOTOR_INPUT_2, HIGH);
            break;
        case DC_MOTOR_STOP:
            Gpio_WritePinValue(DC_MOTOR_PORT, DC_MOTOR_INPUT_1, LOW);
            Gpio_WritePinValue(DC_MOTOR_PORT, DC_MOTOR_INPUT_2, LOW);
            break;
        default:
            break;
    }
}
/*
* Function : DC_Motor_Stop
* Input : void
* Output : void
* Description :
* Stop DC Motor
*/
void DC_Motor_Stop(void){
    Gpio_WritePinValue(DC_MOTOR_PORT, DC_MOTOR_INPUT_1, LOW);
    Gpio_WritePinValue(DC_MOTOR_PORT, DC_MOTOR_INPUT_2, LOW);
}
