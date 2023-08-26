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
 *                                Functions                                    *
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

void update_dashboard(FrameType * frame_data_ptr){
	/* clear the LCD display */
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,3,"Speed:    % Direction: ");
	LCD_displayStringRowColumn(1,7,"Time: xx:xx:xx AM");
	LCD_moveCursor(0, 10);
	LCD_intgerToString(frame_data_ptr->motor_speed);
	LCD_moveCursor(0, 26);
	if (frame_data_ptr->second_motor_direction == 'L' ){
	LCD_displayCharacter('-');
	}else
	{
	LCD_displayCharacter('+');
	}
	LCD_moveCursor(0, 27);
	LCD_intgerToString(frame_data_ptr->wheels_angle);
	// LCD_displayStringRowColumn(0,10,speed_str);
	////	LCD_displayStringRowColumn(0,26,direction_str);
}

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
		//		delay_ms(4000); /* wait four seconds */
	
	}

	return 0;
}
