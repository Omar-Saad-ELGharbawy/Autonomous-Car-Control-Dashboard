/* *******************************************************
 *	main.c
 *	Communicating and Controlling an Autonomous Car Prototype
 *
 * Author: Omar Saad
 *
 *********************************************************/

/* *****************************************************************************
 *                                  Includes                                   *
 *******************************************************************************/
#include "MCAL/Gpio/Gpio.h"
#include "MCAL/Rcc/Rcc.h"
#include "MCAL/Rcc/Rcc_Private.h"
#include "MCAL/Usart/Usart.h"
#include "MCAL/PWM/PWM.h"
#include "MCAL/Systick_Timer/Systick_Timer.h"

#include "HAL/Lcd/Lcd.h"
#include "HAL/DC_Motor/DC_Motor.h"
#include "HAL/Servo_Motor/Servo_Motor.h"

#include "Libraries/Std_Types.h"
#include "Libraries/Utils.h"
#include "Services/Services.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* USE CASES*/
#define RECEIVE_FRAME 0
#define CHECK_FRAME   1
#define EXTRACT_DATA  2
#define CHECK_DATA    3
#define MOVE_MOTORS   4

/* DC Motor Directions */
#define DC_MOTOR_FORWARD ANTI_CLOCKWISE
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
			if (g_hours == 24){
				g_hours = 0;
				g_day_night[0] = 'P';
				g_day_night[1] = 'M';
			}
		}
	}
	update_time_dashboard(g_seconds,g_minutes, g_hours,g_day_night);
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

//	Servo_Motor_SetAngle(99);
////	delay_ms(85); //1.4
//	delay_ms(200); //1.34
//	Servo_Motor_SetAngle(0);

//	DC_Motor_SetDirection(DC_MOTOR_FORWARD);

//	setup_PWM_1();
//	set_PWM_1_duty_cycle(45);


//	setup_PWM_2();
//
//	set_PWM_duty_cycle(100);
//
//
//	DC_Motor_SetDirection(DC_MOTOR_FORWARD);

	//	delay_ms(2000); /* wait 2 seconds */
	LCD_clearScreen();


	/*******************************************************************************
	 *                                 Variables                                   *
	 *******************************************************************************/

	while(1){

		uint8 frame[32];
		FrameType frame_data;

		switch (use_case)
		{
		case RECEIVE_FRAME :
//			LCD_displayStringRowColumn(0,3,"Hi ");
			Uart2_ReceiveString(frame);
			use_case = CHECK_FRAME;
			break;
		case CHECK_FRAME:
			if(check_frame(frame)){
				Usart2_TransmitString("  Valid Frame : ");
				Usart2_TransmitString(frame);
				use_case = EXTRACT_DATA;
			} else {
				//Un-Valid Frame
				Usart2_TransmitString(frame);
				Usart2_TransmitString("  Un-Valid Frame \n Please Enter Valid Frame :");
				use_case = RECEIVE_FRAME;
			}
			break;
		case EXTRACT_DATA :
			extract_data(frame,&frame_data);
			use_case = CHECK_DATA;
			break;
		case CHECK_DATA :
			if(check_data(&frame_data)){
				Usart2_TransmitString("\n Valid Data ");
				use_case = MOVE_MOTORS;
			} else {
				Usart2_TransmitString(frame);
				Usart2_TransmitString("\n Un-Valid Data \n Please Enter Valid Data :");
				use_case = RECEIVE_FRAME;
			}
			break;
		case MOVE_MOTORS :
			/* Update LCD Dashboard with frame data*/
			update_frame_dashboard(&frame_data);
			/* Set DC Motor Speed and Direction */
			DC_Motor_SetSpeed(frame_data.motor_speed);
			if (frame_data.first_motor_direction == 'F'){
				DC_Motor_SetDirection(DC_MOTOR_FORWARD);
			}else if(frame_data.first_motor_direction == 'B'){
				DC_Motor_SetDirection(DC_MOTOR_BACKWARD);
			}
			/* Set Stepper Motor Angle and Direction */
			Servo_Motor_SetAngle(frame_data.wheels_angle);
			/* Ready for another frame */
			use_case = RECEIVE_FRAME;
			break;
		default:
			use_case = CHECK_FRAME;
			break;
		}
	}

	return 0;
}
