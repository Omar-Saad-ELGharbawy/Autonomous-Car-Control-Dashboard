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
/* 
 * Description: Function to receive frame from the user and check if frame is ture or false. 
 * Frame is true only if it ends with E at index 7 and it consists of 8 bytes 
 * Inputs: pointer to frame
 * Output: void
 */
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

/*
 * Description: Function to extract data from frame and store it in strcut data type for frame
* Extracted Data :
* - Speed : 3 Bytes
* - Angle : 2 Bytes
* - first_motor_direction : 1 Byte
* - second_motor_direction : 1 Byte
* Inputs: pointer to frame, pointer to frame data structure
* Output: void
*/
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
	if (frame_data_ptr->second_motor_direction == 'L' ){
	angle = -angle;
	}
	frame_data_ptr->wheels_angle = angle;
}

/*
 * Description: Function to check if data extracted from frame is ture or false. 
 * Data is true only if :
 * - The speed is between 0 and 100
 * - The angle is between -45 and 45
 * - first_motor_direction is F or B
 * - second_motor_direction is R or L
 * Inputs: pointer to frame data structure
 * Output: void
*/
uint8 check_data(FrameType * frame_data_ptr){
	if( (frame_data_ptr->motor_speed <= 100) && (frame_data_ptr->motor_speed >= 0)
		&& (frame_data_ptr->wheels_angle <= 45) && (frame_data_ptr->wheels_angle >= -45)
		&& ((frame_data_ptr->first_motor_direction == 'F') || (frame_data_ptr->first_motor_direction == 'B'))
		&& ((frame_data_ptr->second_motor_direction == 'R') || (frame_data_ptr->second_motor_direction == 'L'))){
		return VALID_FRAME;
	}else {
		return UN_VALID_FRAME;
	}
}
/*
 * Description: Function to update LCD Dashboard with frame data :
 * - DC Motor Speed
 * - Servo Motor Angle
 * Inputs: pointer to frame data structure
 * Output: void
*/
void update_frame_dashboard(FrameType * frame_data_ptr){
	LCD_displayStringRowColumn(0,3,"Speed:    % Direction:   ");
	LCD_moveCursor(0, 10);
	LCD_intgerToString(frame_data_ptr->motor_speed);
	LCD_moveCursor(0, 26);
	LCD_intgerToString(frame_data_ptr->wheels_angle);
}
/*
 * Description: Function to update LCD Dashboard with time data :
 * - Seconds
 * - Minutes
 * - Hours
 * - Day or Night
 * inputs : seconds,minutes,hours,g_day_night
 * Output: void
*/
void update_time_dashboard(uint8 seconds, uint8 minutes, uint8 hours,uint8 g_day_night[]){
	/* clear the LCD display */
	LCD_moveCursor(1, 7);
	LCD_displayStringRowColumn(1,9,"Time:00:00:00");
	if(seconds <10){
		LCD_moveCursor(1, 20);
		LCD_intgerToString(0);
		LCD_moveCursor(1, 21);
		LCD_intgerToString(seconds);
	}else{
		LCD_moveCursor(1, 20);
		LCD_intgerToString(seconds);
	}
	if(minutes <10){
		LCD_moveCursor(1, 17);
		LCD_intgerToString(0);
		LCD_moveCursor(1, 18);
		LCD_intgerToString(minutes);
	}else{
		LCD_moveCursor(1, 17);
		LCD_intgerToString(minutes);
	}
	if(hours <10){
		LCD_moveCursor(1, 14);
		LCD_intgerToString(0);
		LCD_moveCursor(1, 15);
		LCD_intgerToString(hours);
	}else{
		LCD_moveCursor(1, 14);
		LCD_intgerToString(hours);
	}
	LCD_displayStringRowColumn(1,24,g_day_night);
}

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
