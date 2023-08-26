/* *****************************************************************************
* Module: LCD
 *
 * File Name: Lcd.h
 *
 * Description: Interface file for the STM32 LCD driver
 *
 * Created on: Aug 26, 2023
 *
 * Author: Omar Saad
 *
 *******************************************************************************/

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

/* LCD Data bits mode configuration, its value should be 4 or 8*/
#define LCD_DATA_BITS_MODE 8

#if((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))

#error "Number of Data bits should be equal to 4 or 8"

#endif

/* LCD HW Ports and Pins Ids */
#define LCD_RS_PORT_ID                 GPIO_D
#define LCD_RS_PIN_ID                  10

#define LCD_E_PORT_ID                  GPIO_D
#define LCD_E_PIN_ID                   11

#define LCD_DATA_PORT_ID               GPIO_D

#if (LCD_DATA_BITS_MODE == 4)

#define LCD_DB4_PIN_ID                 0
#define LCD_DB5_PIN_ID                 1
#define LCD_DB6_PIN_ID                 2
#define LCD_DB7_PIN_ID                 3

#endif


#endif /* LCD_INTERFACE_H_ */
