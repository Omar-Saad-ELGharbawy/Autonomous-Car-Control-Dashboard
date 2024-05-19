/* *******************************************************
 *	main.c
 *
 *	Communicating and Controlling an Autonomous Car Prototype
 *
 * Author: Omar Saad
 *
 *********************************************************/

/* *****************************************************************************
 *                                  Includes                                   *
 *******************************************************************************/
#include "../MCAL/Rcc/Rcc.h"
#include "../MCAL/Gpio/Gpio.h"
#include "../MCAL/Usart/Usart.h"
#include "../MCAL/PWM/PWM.h"
#include "../MCAL/Systick_Timer/Systick_Timer.h"

#include "../HAL/Lcd/Lcd.h"
#include "../HAL/DC_Motor/DC_Motor.h"
#include "../HAL/Servo_Motor/Servo_Motor.h"

#include "../Services/Includes/Services.h"
#include "../Services/Includes/Dashboard.h"
#include "../Services/Includes/Frame.h"

#include "../Libraries/Std_Types.h"
#include "../Libraries/Utils.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* USE CASES*/
#define RECEIVE_FRAME 0
#define CHECK_FRAME   1
#define EXTRACT_DATA  2
#define CHECK_DATA    3
#define CONTROL_CAR   4

/* DC Motor Directions */
#define DC_MOTOR_FORWARD  ANTI_CLOCKWISE
#define DC_MOTOR_BACKWARD CLOCKWISE

/*******************************************************************************
 *                            Global Variables                                 *
 *******************************************************************************/
uint8 use_case = RECEIVE_FRAME;

uint8 g_seconds = 0;
uint8 g_minutes = 0;
uint8 g_hours = 0;
uint8 g_day_night [] = "AM";

/*******************************************************************************
 *                            Interrupt CallBack                               *
 *******************************************************************************/

/*
 * Description: Function to be called every 1 second to update
 * the time on the LCD Dashboard
 * Inputs: void
 * Output: void
*/
void SysTick_callBack()
{
	/*Update Seconds, minutes & Hours for dashboard view */
	g_seconds++;
	if (g_seconds == 60){
		g_seconds = 0;
		g_minutes++;
		if (g_minutes == 60){
			g_minutes = 0;
			g_hours++;
			if (g_hours == 12){
				g_hours = 0;
				if (g_day_night[0] == 'A'){
					g_day_night[0] = 'P';
				}else
				{
					g_day_night[0] = 'A';
				}
			}
		}
	}
	Dashboard_UpdateTime(g_seconds,g_minutes, g_hours,g_day_night);
}

/*******************************************************************************
 *                                   Main                                      *
 *******************************************************************************/

int main () {

	/*SET frequency to 1 MHz (set Prescaler to 16) */
//	RCC_CFGR |= (0x0B << 4);

	/* ***********************Initializations*********************** */
	/* Initialize RCC*/
	Rcc_Init();
	/* Initialize GPIO Driver */
	//	 Gpio_Init();
	/* Initialize the LCD */
	LCD_init();
	/* Initialize the USART */
	Usart2_Init();
	/* Initialize the DC Motors */
	DC_Motor_Init();
	/* Initialize the Servo Motor */
	Servo_Motor_Init();
	/* Initialize the Systick Timer */
	SysTick_Init();
	SysTic_setCallBack(SysTick_callBack);

	/* ***********************Dashboard View*********************** */

	LCD_clearScreen();
	LCD_displayString("            WELCOME");
	LCD_moveCursor(1, 9);
	LCD_displayString("Time:00:00:00  AM");

	/*******************************************************************************
	 *                                 Variables                                   *
	 *******************************************************************************/
		uint8 frame[32];
//		uint8 * frame;
		FrameType frame_data;

	/* ***********************Main Loop*********************** */
	while(1){


	/*******************************************************************************
	 *                                 Handling Cases                              *
	 *******************************************************************************/

		switch (use_case)
		{

		case RECEIVE_FRAME :
		/* 
		 * Receive Frame from the user to control the car
		 * Frame Format : 1st Motor Speed, 1st Motor Direction, 2nd Motor Direction, Wheels Angle
		*/
			Uart2_ReceiveString(frame);
			use_case = CHECK_FRAME;
			break;
		case CHECK_FRAME:
			/*
			 * Check if the frame format is valid or not
			 * If it's invalid then send an error message and go back to receive mode.
			 * Valid Frame : 8 bytes ends with E
			 * Valid Frame Example : 076F18LE
			*/
			if(Frame_IsValid(frame)){
				Usart2_TransmitString("Valid Frame ");
				use_case = EXTRACT_DATA;
			} else {
				//Un-Valid Frame
				Usart2_TransmitString("Un-Valid Frame : ");
				Usart2_TransmitString(frame);
				Usart2_TransmitString(" Please Enter Valid Frame > ");
				use_case = RECEIVE_FRAME;
			}
			break;
		case EXTRACT_DATA :
			/*
			* Extract the data from the frame and store it in frame_data structure
			* Frame Format : 1st Motor Speed, 1st Motor Direction, 2nd Motor Direction, Wheels Angle
			*/
			Frame_ExtractData(frame,&frame_data);
			use_case = CHECK_DATA;
			break;
		case CHECK_DATA :
			/*
			* Check if the data is valid or not
			* If it's invalid then send an error message and go back to receive mode.
			* Valid Data : 1st Motor Speed (0 -> 100), 1st Motor Direction (F or B), 2nd Motor Direction (R or L), Wheels Angle (0 -> 45)
			* Valid Data Example : 076F18
			*/
			if(Frame_CheckData(&frame_data)){
				Usart2_TransmitString("and Valid Data : ");
				Usart2_TransmitString(frame);
				use_case = CONTROL_CAR;
			} else {
				Usart2_TransmitString("but Un-Valid Data :");
				Usart2_TransmitString(frame);
				Usart2_TransmitString(" Please Enter Valid Data > ");
				use_case = RECEIVE_FRAME;
			}
			break;
		case CONTROL_CAR :
			/*
			* Control the car based on the frame data :
			* Move the DC Motor with the received Speed
			* Move the Servo Motor with the received Angle
			*/

			/* Update LCD Dashboard with frame data*/
			Dashboard_UpdateFrame(&frame_data);
			/* Set DC Motor Speed and Direction */
			DC_Motor_SetSpeed(frame_data.motor_speed);
			if (frame_data.first_motor_direction == 'F'){
				DC_Motor_SetDirection(DC_MOTOR_FORWARD);
			}else if(frame_data.first_motor_direction == 'B'){
				DC_Motor_SetDirection(DC_MOTOR_BACKWARD);
			}
			/* Set Servo Motor Angle and Direction */
			Servo_Motor_SetAngle(frame_data.wheels_angle);
			/* Ready for another frame */
			Usart2_TransmitString(" > You Can Enter New Frame > ");
			use_case = RECEIVE_FRAME;
			break;
		default:
			use_case = CHECK_FRAME;
			break;
		}
	}

	return 0;
}
