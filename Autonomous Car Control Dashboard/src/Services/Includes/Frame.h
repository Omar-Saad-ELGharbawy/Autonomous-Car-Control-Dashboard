/* *****************************************************************************
 *
 * File Name: Frame.h
 *
 * Description: Header file for Common Services Functions
 *
 * Created on: Aug 26, 2023
 *
 * Author: Omar Saad
 *
 *******************************************************************************/

#ifndef FRAME_H_
#define FRAME_H_

#include "Services.h"
#include "../../HAL/Lcd/Lcd.h"
#include "../../Libraries/Std_Types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Frame Conditions */
#define VALID_FRAME 1
#define UN_VALID_FRAME 0

/*******************************************************************************
 *                                Typedef Structs                              *
 *******************************************************************************/

/* Struct data type of frame data contains :
uint8 motor_speed  (0 -> 100)
uint8 first_motor_direction (F or B)
uint8 second_motor_direction (R or L)
uint8 wheels_angle  (-45 -> 45)
*/
typedef struct {
	sint8 motor_speed;
	uint8 first_motor_direction;
	uint8 second_motor_direction;
	sint8 wheels_angle;
} FrameType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* 
 * Description: Function to receive frame from the user and check if frame is ture or false. 
 * Frame is true only if it ends with E at index 7 and it consists of 8 bytes 
 * Inputs: pointer to frame
 * Output: void
 */
uint8 Frame_IsValid(uint8 *frame);

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
void Frame_ExtractData(uint8 *frame , FrameType * frame_data_ptr);

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
uint8 Frame_CheckData(FrameType * frame_data_ptr);


#endif /* FRAME_H_ */
