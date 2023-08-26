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
#include "MCAL/Usart/Usart.h"
#include "HAL/Lcd/Lcd.h"
#include "HAL/DC_Motor/DC_Motor.h"
#include "Libraries/Std_Types.h"
#include "Libraries/Utils.h"
#include "Services/Services.h"

#include "MCAL/PWM/PWM.h"

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

int main () {

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

//	setup_PWM();
//
//	set_PWM_duty_cycle(100);
//
//
//	DC_Motor_SetDirection(DC_MOTOR_FORWARD);

	//	delay_ms(2000); /* wait 2 seconds */

	/*******************************************************************************
	 *                                 Variables                                   *
	 *******************************************************************************/

	while(1){

		uint8 frame[32];
		FrameType frame_data;

		switch (use_case)
		{
		case RECEIVE_FRAME :
			Uart2_ReceiveString(frame);
			use_case = CHECK_FRAME;
			break;
		case CHECK_FRAME:
			if(check_frame(frame)){
				Usart2_TransmitString("Valid Frame : ");
				Usart2_TransmitString(frame);
				use_case = EXTRACT_DATA;
			} else {
				//Un-Valid Frame
				Usart2_TransmitString("Un-Valid Frame \n Please Enter Valid Frame :");
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
				Usart2_TransmitString("\n Un-Valid Data \n Please Enter Valid Data :");
//				Usart2_TransmitString(frame);
				use_case = RECEIVE_FRAME;
			}
			break;
		case MOVE_MOTORS :
			/* Update LCD Dashboard*/
			update_dashboard(&frame_data);
			/* Set DC Motor Speed and Direction */
			DC_Motor_SetSpeed(frame_data.motor_speed);
			if (frame_data.first_motor_direction == 'F'){
				DC_Motor_SetDirection(DC_MOTOR_FORWARD);
			}else if(frame_data.first_motor_direction == 'B'){
				DC_Motor_SetDirection(DC_MOTOR_BACKWARD);
			}
			/* Set Stepper Motor Angle and Direction */

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
