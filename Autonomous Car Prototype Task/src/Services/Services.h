/* *****************************************************************************
 *
 * File Name: Services.h
 *
 * Description: Source file for Services Functions
 *
 * Created on: Aug 26, 2023
 *
 * Author: Omar Saad
 *
 *******************************************************************************/


#ifndef SERVICES_H_
#define SERVICES_H_

#include "../Libraries/Std_Types.h"


#define ONE_MS_TICKS 1000
#define INVALID_INTEGER -1


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

int convertToInt(uint8 str[]);

char* convertToString(int number);

void delay_ms(uint32 ms);


#endif /* SERVICES_H_ */
