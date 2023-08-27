/* *****************************************************************************
 *
 * File Name: Services.c
 *
 * Description: Source file for Services Functions
 *
 * Created on: Aug 26, 2023
 *
 * Author: Omar Saad
 *
 *******************************************************************************/

#include "Services.h"


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/



uint8 check_frame(uint8 *frame){
	uint8 frame_size = 0;
	uint8 i=0;
	while(frame[i] != '\0'){
		frame_size++;
		i++;
	}
	/* Check frame : Frame is true only if it ends with E at index 7 and it consists of 8 bytes */
	if((frame[7] == 'E') &&(frame_size == 8) ){
		return VALID_FRAME;
	}else {
		return UN_VALID_FRAME;
	}
}

void extract_data(uint8 *frame , FrameType * frame_data_ptr){
	/* Extract data from Frame*/
		//	uint8 frame_size;
	uint8 speed_str[4];
	uint8 angle_str[3];

	uint8 first_motor_direction;
	uint8 second_motor_direction;

	/* Extract the first 3 Bytes for Speed*/
	for (uint8 i=0; i<3; i++){
	speed_str[i] = frame[i];
	}
	speed_str[3] = '\0';
	/* Convert String to Integer */
	sint8 speed = convertToInt(speed_str);
	frame_data_ptr->motor_speed = speed;

	/* Extract Byte 4 for first motor direction (F or B)*/
	first_motor_direction = frame[3];
	frame_data_ptr->first_motor_direction = first_motor_direction;
	/* Extract Byte 6 for second motor direction (R or L)*/
	second_motor_direction = frame[6];
	frame_data_ptr->second_motor_direction = second_motor_direction;


	/* Extract the last 2 Bytes for Angle*/
	for (uint8 i=0; i<2; i++){
	angle_str[i] = frame[i+4];
	}
	speed_str[2] = '\0';
	/* Convert angle String to Integer */
	int angle = convertToInt(angle_str);

	frame_data_ptr->wheels_angle = angle;
}

uint8 check_data(FrameType * frame_data_ptr){
	/* Check Data : Data is true only if :
	- The speed is between 0 and 100
	- The angle is between -45 and 45
	- first_motor_direction is F or B
	- second_motor_direction is R or L
	*/
	if( (frame_data_ptr->motor_speed <= 100) && (frame_data_ptr->motor_speed >= 0)
		&& (frame_data_ptr->wheels_angle <= 45) && (frame_data_ptr->wheels_angle >= -45)
		&& ((frame_data_ptr->first_motor_direction == 'F') || (frame_data_ptr->first_motor_direction == 'B'))
		&& ((frame_data_ptr->second_motor_direction == 'R') || (frame_data_ptr->second_motor_direction == 'L'))){
		return VALID_FRAME;
	}else {
		return UN_VALID_FRAME;
	}
}

void update_frame_dashboard(FrameType * frame_data_ptr){
	/* clear the LCD display */
//	LCD_clearScreen();
	LCD_displayStringRowColumn(0,3,"Speed:    % Direction: ");
	LCD_moveCursor(0, 9);
	LCD_intgerToString(frame_data_ptr->motor_speed);
	LCD_moveCursor(0, 27);
	if (frame_data_ptr->second_motor_direction == 'L' ){
	LCD_displayCharacter('-');
	}else
	{
	LCD_displayCharacter('+');
	}
	LCD_moveCursor(0, 28);
	LCD_intgerToString(frame_data_ptr->wheels_angle);
}

/* Update LCD Dashboard with time data*/
void update_time_dashboard(uint8 seconds, uint8 minutes, uint8 hours,uint8 g_day_night[]){
	/* clear the LCD display */
	LCD_displayStringRowColumn(1,7,"Time:   :  :   ");
	LCD_moveCursor(1, 13);
	LCD_intgerToString(hours);
	LCD_moveCursor(1, 16);
	LCD_intgerToString(minutes);
	LCD_moveCursor(1, 19);
	LCD_intgerToString(seconds);
	LCD_displayStringRowColumn(1,22,g_day_night);
}


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


void delay_ms(uint32 ms){
	/*wait 1s by for loop*/
	for(uint32 i = 0; i < ms; i++)
	{}
}
