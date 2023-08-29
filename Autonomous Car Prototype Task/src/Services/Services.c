/* *****************************************************************************
 *
 * File Name: Services.c
 *
 * Description: Source file for Common Services Functions
 *
 * Created on: Aug 26, 2023
 *
 * Author: Omar Saad
 *
 *******************************************************************************/

#include "Includes/Services.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description: Function to convert string to integer
 * Inputs: pointer to string
 * Output: integer
*/
int convertToInt(uint8 str[]) {
    int result = 0;
    int i = 0;

    // Process each digit in the string
    while (str[i] != '\0') {
        // Check if the character is a digit
        if (str[i] >= '0' && str[i] <= '9') {
            // Convert the digit character to its integer value
            int digit = str[i] - '0';

            // Update the result by multiplying it by 10 and adding the digit
            result = result * 10 + digit;
        } else {
            // Invalid character found, break the loop
            return INVALID_INTEGER;
        }
        i++;
    }
    return result;
}

/*
 * Description: Function to convert integer to string
 * Inputs: integer
 * Output: pointer to string
*/
char* convertToString(int number) {
    int numDigits = 0;
    int temp = number;

    // Count the number of digits in the integer
    if (number == 0) {
        numDigits = 1;
    } else {
        if (number < 0) {
            numDigits++; // Account for the negative sign
            temp = -temp; // Make the number positive for digit extraction
        }

        while (temp != 0) {
            numDigits++;
            temp /= 10;
        }
    }
    // Allocate memory for the string representation
    char* str = (char *)malloc((numDigits + 1) * sizeof(char));

    // Handle the case of a negative number
    if (number < 0) {
        str[0] = '-';
        number = -number;
    }
    // Convert each digit to a character and store in the string
    int i = numDigits - 1;
    while (number != 0) {
        str[i] = '0' + (number % 10);
        number /= 10;
        i--;
    }
    // Null-terminate the string
    str[numDigits] = '\0';

    return str;
}

/*
 * Description: Function to delay for 1ms
 * Inputs: void
 * Output: void
*/
void delay_ms(uint32 ms){
	/*wait 1s by for loop*/
	for(uint32 i = 0; i < ms*ONE_MS_TICKS; i++)
	{}
}
