/*
 * Servo_Motor.c
 *
 *  Created on: Aug 26, 2023
 *      Author: Omar Saad
 */

#include "Servo_Motor.h"

#include "../../MCAL/PWM/PWM.h"
#include "../../Services/Services.h"

/*
    * Description: Function to initialize the servo motor by 
    * initializing the PWM
    * Inputs: void
    * Output: void
*/
void Servo_Motor_Init(void){
    /* Initialize the PWM */
    setup_PWM_2();
}
/*
    * Description: Function to set the angle of the servo motor
    * Inputs: angle
    * Output: void
*/
void Servo_Motor_SetAngle(sint8 angle){
    /* Set the angle of the servo motor */
	set_PWM_2_CCR2(1500 + (angle*10));
}
