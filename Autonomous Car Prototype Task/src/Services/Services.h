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


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define ONE_MS_TICKS 1000
#define INVALID_INTEGER -1

/* Frame Conditions */
#define VALID_FRAME 1
#define UN_VALID_FRAME 0

/* Struct data type of frame data contains :
uint8 motor_speed  (0 -> 100)
uint8 first_motor_direction (F or B)
uint8 second_motor_direction (R or L)
uint8 wheels_angle  (0 -> 45)
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
uint8 check_frame(uint8 *frame);

void extract_data(uint8 *frame , FrameType * frame_data_ptr);

uint8 check_data(FrameType * frame_data_ptr);

void update_frame_dashboard(FrameType * frame_data_ptr);

void update_time_dashboard(uint8 seconds, uint8 minutes, uint8 hours,uint8 g_day_night[]);

int convertToInt(uint8 str[]);

char* convertToString(int number);

void delay_ms(uint32 ms);


#endif /* SERVICES_H_ */
