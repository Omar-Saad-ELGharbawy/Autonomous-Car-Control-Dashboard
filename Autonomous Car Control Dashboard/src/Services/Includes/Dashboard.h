/* *****************************************************************************
 *
 * File Name: Dashboard.h
 *
 * Description: Header file for Dashboard Functions
 *
 * Author: Omar Saad
 *
 *******************************************************************************/

#ifndef DASHBOARD_H_
#define DASHBOARD_H_

#include "Services.h"
#include "Frame.h"
#include "../../HAL/Lcd/Lcd.h"
#include "../../Libraries/Std_Types.h"

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description: Function to update LCD Dashboard with frame data :
 * - DC Motor Speed
 * - Servo Motor Angle
 * Inputs: pointer to frame data structure
 * Output: void
*/
void Dashboard_UpdateFrame(FrameType * frame_data_ptr);

/*
 * Description: Function to update LCD Dashboard with time data :
 * - Seconds
 * - Minutes
 * - Hours
 * - Day or Night
 * inputs : seconds,minutes,hours,g_day_night
 * Output: void
*/
void Dashboard_UpdateTime(uint8 seconds, uint8 minutes, uint8 hours,uint8 g_day_night[]);


#endif /* SERVICES_INCLUDES_DASHBOARD_H_ */

