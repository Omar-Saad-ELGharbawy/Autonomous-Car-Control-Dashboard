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
// #include "DC_Motor_Interface.h"


void DC_Motor_Init(void){
    Rcc_Enable(DC_MOTOR_PORT);

    /* Configure Output pins for DC Motor */
	Gpio_ConfigPin(DC_MOTOR_PORT, DC_MOTOR_INPUT_1, GPIO_OUTPUT, GPIO_PUSH_PULL, NOT_INPUT);
	Gpio_WritePinValue(DC_MOTOR_PORT, DC_MOTOR_INPUT_1, LOW);
	Gpio_ConfigPin(DC_MOTOR_PORT, DC_MOTOR_INPUT_2, GPIO_OUTPUT, GPIO_PUSH_PULL, NOT_INPUT);
	Gpio_WritePinValue(DC_MOTOR_PORT, DC_MOTOR_INPUT_1, LOW);
    Gpio_ConfigPin(DC_MOTOR_PORT, DC_MOTOR_ENABLE_1, GPIO_OUTPUT, GPIO_PUSH_PULL, NOT_INPUT);
    Gpio_WritePinValue(DC_MOTOR_PORT, DC_MOTOR_ENABLE_1, HIGH);
}

void DC_Motor_SetSpeed(uint8 speed){
    if(speed > 100){
        speed = 100;
    }
    Gpio_WritePinValue(DC_MOTOR_PORT, DC_MOTOR_INPUT_1, speed);
    // pwm 
}

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

void DC_Motor_Stop(void){
    Gpio_WritePinValue(DC_MOTOR_PORT, DC_MOTOR_INPUT_1, LOW);
    Gpio_WritePinValue(DC_MOTOR_PORT, DC_MOTOR_INPUT_2, LOW);
}





