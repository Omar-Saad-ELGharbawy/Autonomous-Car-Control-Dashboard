/* *****************************************************************************
 *
 * File Name: Services.c
 *
 * Description: Source file for Frame Functions
 *
 * Created on: Aug 26, 2023
 *
 * Author: Omar Saad
 *
 *******************************************************************************/
#include "Frame.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/* 
 * Description: Function to receive frame from the user and check if frame is ture or false. 
 * Frame is true only if it ends with E at index 7 and it consists of 8 bytes 
 * Inputs: pointer to frame
 * Output: void
 */
uint8 Frame_IsValid(uint8 *frame){
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
void Frame_ExtractData(uint8 *frame , FrameType * frame_data_ptr){
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
uint8 Frame_CheckData(FrameType * frame_data_ptr){
	if( (frame_data_ptr->motor_speed <= 100) && (frame_data_ptr->motor_speed >= 0)
		&& (frame_data_ptr->wheels_angle <= 45) && (frame_data_ptr->wheels_angle >= -45)
		&& ((frame_data_ptr->first_motor_direction == 'F') || (frame_data_ptr->first_motor_direction == 'B'))
		&& ((frame_data_ptr->second_motor_direction == 'R') || (frame_data_ptr->second_motor_direction == 'L'))){
		return VALID_FRAME;
	}else {
		return UN_VALID_FRAME;
	}
}