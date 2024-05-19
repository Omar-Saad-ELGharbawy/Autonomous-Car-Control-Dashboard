/* *****************************************************************************
 * Module: 𝓤𝓼𝓪𝓻𝓽
 *
 * File Name: Usart.c
 *
 * Description: Source file for the STM32 Usart driver
 *
 * Created on: Aug 25, 2023
 *
 * Author: Omar Saad
 *
 *******************************************************************************/

#include "Usart.h"

#include "../../Libraries/Macros.h"
#include "../Rcc/Rcc.h"
#include "../Gpio/Gpio.h"
#include "stm32f401xe.h"

/*
  * Function : Usart2_Init
  * Input : void
  * Output : void
  * Description :
  * Enable Clock for used GPIO PORTs using Static Configurationin .
  * Setup USART2 for serial communication
  * Configure GPIO Pins for USART2
*/
void Usart2_Init(void) {
  Rcc_Enable(RCC_USART2);
  Rcc_Enable(RCC_GPIOA);
  /* Configure GPIO pins for USART2 */

  Gpio_ConfigPin(GPIO_A, 2, GPIO_AF, GPIO_PUSH_PULL,NOT_INPUT);
  Gpio_ConfigPin(GPIO_A, 3, GPIO_AF, GPIO_PUSH_PULL,NOT_INPUT);
  /* Alternate function selection of AF7 for port A for bits 2 & 3 to work as RX and TX */
  INSERT_4BITS_BLOCK(GPIOA->AFR[0], 2, 7);
  INSERT_4BITS_BLOCK(GPIOA->AFR[0], 3, 7);

  RCC->APB1ENR |= 1 << RCC_APB1ENR_USART2EN_Pos;

  USART2->CR1 &= ~(1 << USART_CR1_M_Pos);

  USART2->CR2 &= ~(USART_CR2_STOP);

  USART2->CR1 &= ~(1 << USART_CR1_OVER8_Pos);

  USART2->BRR = 0x683;  // Baud Rate 9600

  /* Enable Transmission block */
  SET_BIT(USART2->CR1, 3);

  /* Enable Receive block */
  SET_BIT(USART2->CR1, 2);

  /* Enable USART2 */
  SET_BIT(USART2->CR1, 13);
}
/*
  * Function : Usart2_TransmitByte
  * Input : Byte
  * Output : uint8
  * Description :
  * Transmit Byte using USART2
*/
uint8 Usart2_TransmitByte(uint8 Byte){
  /*
    * Check if the transmit data register is empty
    * If it is empty, then transmit the byte
    * If it is not empty, then return NOK
  */
  if(BIT_IS_SET(USART2->SR,7)){
    USART2->DR = Byte;
    /*  Wait until the transmission is complete
      * by checking the transmission complete flag
      * in the status register
    */
    while(BIT_IS_CLEAR(USART2->SR ,6));
    /* Clear the transmission complete flag */
    CLEAR_BIT( USART2->SR, 6) ;
    return OK;
  }
  return NOK;
}
/*
  * Function : Usart2_TransmitString
  * Input : Str
  * Output : void
  * Description :
  * Transmit String using USART2
*/
void Usart2_TransmitString(const uint8* Str) {
  unsigned char i = 0;
  while (Str[i] != '\0') {
	  Usart2_TransmitByte(Str[i]);
      i++;
    }
  }
/*
  * Function : Usart2_ReceiveByte
  * Input : void
  * Output : uint8
  * Description :
  * Receive Byte using USART2
*/
uint8 Usart2_ReceiveByte(void){
  /* Wait until the data is received by checking the
  * Receive Data Ready flag in the status register
  */
  while(BIT_IS_CLEAR(USART2->SR ,5)){}
  return USART2->DR;
}
/*
  * Function : Usart2_ReceiveString
  * Input : Str
  * Output : void
  * Description :
  * Receive String using USART2
*/
void Uart2_ReceiveString(uint8 *Str)
{
	uint8 i = 0;
	/* Receive the first byte */
	Str[i] = Usart2_ReceiveByte();
	/* Receive the whole string until the \r */
	while(Str[i] != '\r'){
		i++;
		Str[i] = Usart2_ReceiveByte();
	}
	/* After receiving the whole string plus the '\r', replace the '\r' with '\0' */
	Str[i] = '\0';
}
