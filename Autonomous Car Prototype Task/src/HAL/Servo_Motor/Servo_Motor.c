/*
 * Servo_Motor.c
 *
 *  Created on: Aug 26, 2023
 *      Author: Omar Saad
 */

#include "Servo_Motor.h"

#include "../../MCAL/PWM/PWM.h"


void Servo_Motor_Init(void){
    /* Initialize the PWM */
    setup_PWM_2();
}

void Servo_Motor_SetAngle(uint8 angle){
    /* Set the angle of the servo motor */
	set_PWM_2_duty_cycle(angle);
}
