/* *****************************************************************************
 *
 * File Name: Services.h
 *
 * Description: Header file for Common Services Functions
 *
 * Created on: Aug 26, 2023
 *
 * Author: Omar Saad
 *
 *******************************************************************************/
#ifndef SERVICES_H_
#define SERVICES_H_

#include "../../Libraries/Std_Types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define ONE_MS_TICKS 1000
#define INVALID_INTEGER -1



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description: Function to convert string to integer
 * Inputs: pointer to string
 * Output: integer
*/
int convertToInt(uint8 str[]);

/*
 * Description: Function to convert integer to string
 * Inputs: integer
 * Output: pointer to string
*/
char* convertToString(int number);

/*
 * Description: Function to delay for 1ms
 * Inputs: void
 * Output: void
*/
void delay_ms(uint32 ms);

#endif /* SERVICES_H_ */
