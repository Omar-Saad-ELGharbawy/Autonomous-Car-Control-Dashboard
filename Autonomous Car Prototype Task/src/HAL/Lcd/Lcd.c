/* *****************************************************************************
 * Module: LCD
 *
 * File Name: Lcd.h
 *
 * Description: Source file for the STM32 LCD driver
 *
 * Author: Omar Saad
 *
 *******************************************************************************/
#include "Lcd.h"

#include "../../MCAL/Gpio/Gpio.h"
#include "../../MCAL/Rcc/Rcc.h"
#include "../../Libraries/Macros.h"
#include "../../Libraries/Utils.h"
#include "../../Services/Services.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 4-bits or 8-bits.
 */
void LCD_init(void)
{
	Rcc_Enable(RCC_GPIOD);
	/* Configure the direction for RS and E pins as output pins */
	Gpio_ConfigPin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, GPIO_OUTPUT, GPIO_PUSH_PULL, NOT_INPUT);
	Gpio_ConfigPin(LCD_E_PORT_ID, LCD_E_PIN_ID, GPIO_OUTPUT, GPIO_PUSH_PULL, NOT_INPUT);

	delay_ms(20); /* LCD Power ON delay always > 15ms */

#if (LCD_DATA_BITS_MODE == 4)
	/* Configure 4 pins in the data port as output pins */
	Gpio_ConfigPin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GPIO_OUTPUT, GPIO_PUSH_PULL, NOT_INPUT);
	Gpio_ConfigPin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GPIO_OUTPUT, GPIO_PUSH_PULL, NOT_INPUT);
	Gpio_ConfigPin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GPIO_OUTPUT, GPIO_PUSH_PULL, NOT_INPUT);
	Gpio_ConfigPin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GPIO_OUTPUT, GPIO_PUSH_PULL, NOT_INPUT);

	/* Send for 4 bit initialization of LCD  */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	/* use 2-lines LCD + 4-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);

#elif (LCD_DATA_BITS_MODE == 8)
	/* Configure the 8 pins in LCD_DATA_PORT_ID as output */
	for (uint8 PinId = 0; PinId < LCD_DATA_BITS_MODE; PinId++)
	{
		Gpio_ConfigPin(LCD_DATA_PORT_ID, PinId, GPIO_OUTPUT, GPIO_PUSH_PULL, NOT_INPUT);
	}

	/* use 2-lines LCD + 8-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);

#endif

	LCD_sendCommand(LCD_CURSOR_OFF);	/* cursor off */
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* clear LCD at the beginning */
}

/*
 * Description :
 * Send the required command to the screen
 */
void LCD_sendCommand(uint8 command)
{
	Gpio_WritePinValue(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_LOW); /* Instruction Mode RS=0 */
	delay_ms(1);												  /* delay for processing Tas = 50ns */
	Gpio_WritePinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);  /* Enable LCD E=1 */
	delay_ms(1);												  /* delay for processing Tpw - Tdws = 190ns */

#if (LCD_DATA_BITS_MODE == 4)
	Gpio_WritePinValue(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(command, 4));
	Gpio_WritePinValue(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(command, 5));
	Gpio_WritePinValue(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(command, 6));
	Gpio_WritePinValue(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(command, 7));

	delay_ms(1);												 /* delay for processing Tdsw = 100ns */
	Gpio_WritePinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);	 /* Disable LCD E=0 */
	delay_ms(1);												 /* delay for processing Th = 13ns */
	Gpio_WritePinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH); /* Enable LCD E=1 */
	delay_ms(1);												 /* delay for processing Tpw - Tdws = 190ns */

	Gpio_WritePinValue(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(command, 0));
	Gpio_WritePinValue(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(command, 1));
	Gpio_WritePinValue(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(command, 2));
	Gpio_WritePinValue(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(command, 3));

	delay_ms(1);												/* delay for processing Tdsw = 100ns */
	Gpio_WritePinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW); /* Disable LCD E=0 */
	delay_ms(1);												/* delay for processing Th = 13ns */

#elif (LCD_DATA_BITS_MODE == 8)
	/* out the required command to the data bus D0 --> D7 */
	for (uint8 PinId = 0; PinId < LCD_DATA_BITS_MODE; PinId++)
	{
		Gpio_WritePinValue(LCD_DATA_PORT_ID, PinId, GET_BIT(command, PinId));
	}
	delay_ms(1);												/* delay for processing Tdsw = 100ns */
	Gpio_WritePinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW); /* Disable LCD E=0 */
	delay_ms(1);												/* delay for processing Th = 13ns */
#endif
}

/*
 * Description :
 * Display the required character on the screen
 */
void LCD_displayCharacter(uint8 data)
{
	Gpio_WritePinValue(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH); /* Data Mode RS=1 */
	delay_ms(1);												   /* delay for processing Tas = 50ns */
	Gpio_WritePinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);   /* Enable LCD E=1 */
	delay_ms(1);												   /* delay for processing Tpw - Tdws = 190ns */

#if (LCD_DATA_BITS_MODE == 4)
	Gpio_WritePinValue(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(data, 4));
	Gpio_WritePinValue(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(data, 5));
	Gpio_WritePinValue(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(data, 6));
	Gpio_WritePinValue(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(data, 7));

	delay_ms(1);												 /* delay for processing Tdsw = 100ns */
	Gpio_WritePinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);	 /* Disable LCD E=0 */
	delay_ms(1);												 /* delay for processing Th = 13ns */
	Gpio_WritePinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH); /* Enable LCD E=1 */
	delay_ms(1);												 /* delay for processing Tpw - Tdws = 190ns */

	Gpio_WritePinValue(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(data, 0));
	Gpio_WritePinValue(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(data, 1));
	Gpio_WritePinValue(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(data, 2));
	Gpio_WritePinValue(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(data, 3));

	delay_ms(1);												/* delay for processing Tdsw = 100ns */
	Gpio_WritePinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW); /* Disable LCD E=0 */
	delay_ms(1);												/* delay for processing Th = 13ns */

#elif (LCD_DATA_BITS_MODE == 8)
	/* out the required command to the data bus D0 --> D7 */
	for (uint8 PinId = 0; PinId < LCD_DATA_BITS_MODE; PinId++)
	{
		Gpio_WritePinValue(LCD_DATA_PORT_ID, PinId, GET_BIT(data, PinId));
	}
	delay_ms(1);												/* delay for processing Tdsw = 100ns */
	Gpio_WritePinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW); /* Disable LCD E=0 */
	delay_ms(1);												/* delay for processing Th = 13ns */
#endif
}

/*
 * Description :
 * Display the required string on the screen
 */
void LCD_displayString(const char *Str)
{
	uint8 i = 0;
	while (Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
}

/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void LCD_moveCursor(uint8 row, uint8 col)
{
	uint8 lcd_memory_address;

	/* Calculate the required address in the LCD DDRAM */
	switch (row)
	{
	case 0:
		lcd_memory_address = col;
		break;
	case 1:
		lcd_memory_address = col + 0x40;
		break;
	case 2:
		lcd_memory_address = col + 0x10;
		break;
	case 3:
		lcd_memory_address = col + 0x50;
		break;
	}
	/* Move the LCD cursor to this specific address */
	LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowColumn(uint8 row, uint8 col, const char *Str)
{
	LCD_moveCursor(row, col); /* go to to the required LCD position */
	LCD_displayString(Str);	  /* display the string */
}

/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_intgerToString(int data)
{
	/* convert the data to its corresponding ASCII value, 10 for decimal */
	char* buff = convertToString(data);
	/* Display the string */
	LCD_displayString(buff);
}

/*
 * Description :
 * Send the clear screen command
 */
void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* Send clear display command */
}
