/* *****************************************************************************
 * Module: Usart
 *
 * File Name: Usart.h
 *
 * Description: Source file for the STM32 Usart driver
 *
 * Created on: Aug 25, 2023
 *
 * Author: Omar Saad
 *
 *******************************************************************************/

#include "../../Libraries/Std_Types.h"

#ifndef USART_H
#define USART_H

/*
* Function: Usart2_Init
* ----------------------------
*   Initializes USART2 peripheral
*
*   returns: void
*/
void Usart2_Init(void);

/*
* Function: Usart2_TransmitByte
* ----------------------------
*   Transmits a byte through USART2
*
*   Byte: byte to be transmitted
*
*   returns: ErrorStatus (ERROR or SUCCESS)
*/
uint8 Usart2_TransmitByte(uint8 Byte);

/*
* Function: Usart2_ReceiveByte
* ----------------------------
*   Receives a byte through USART2
*
*   returns: received byte
*/
void Usart2_TransmitString(const char* Str);

/*
* Function: Usart2_ReceiveByte
* ----------------------------
*   Receives a byte through USART2
*
*   returns: received byte
*/
uint8 Usart2_ReceiveByte(void);

/*
* Function: Usart2_ReceiveString
* ----------------------------
*   Receives a string through USART2
*
*   Str: pointer to the string to be received
*
*   returns: void
*/
void Uart2_ReceiveString(uint8 *Str);

#endif /* USART_H */
