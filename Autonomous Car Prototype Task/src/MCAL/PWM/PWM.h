/*
 * PWM.h
 *
 *  Created on: Aug 26, 2023
 *      Author: Omar Saad
 */

#ifndef PWM_H_
#define PWM_H_

#include "../../Libraries/Std_Types.h"

void setup_PWM_1(void);

void setup_PWM_2(void);

void set_PWM_1_duty_cycle(uint8 percentage);

void set_PWM_2_duty_cycle(uint8 percentage);

#endif /* PWM_H_ */
