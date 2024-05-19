/* *****************************************************************************
 *
 * File Name: Dashboard.h
 *
 * Description: Source file for Dashboard Functions
 *
 * Author: Omar Saad
 *
 *******************************************************************************/

#include "Dashboard.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description: Function to update LCD Dashboard with frame data :
 * - DC Motor Speed
 * - Servo Motor Angle
 * Inputs: pointer to frame data structure
 * Output: void
*/
void Dashboard_UpdateFrame(FrameType * frame_data_ptr){
	LCD_displayStringRowColumn(0,3,"Speed:    % Direction:    ");
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
void Dashboard_UpdateTime(uint8 seconds, uint8 minutes, uint8 hours,uint8 g_day_night[]){
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

