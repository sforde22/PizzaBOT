/*
*
*   uart.c
*
*
*
*   @author
*   @date
*/

#include <inc/tm4c123gh6pm.h>
#include <stdint.h>
#include "uart.h"

void uart_init(void){
	//TODO
  //enable clock to GPIO port B
  SYSCTL_RCGCGPIO_R |= 0x2;

  //enable clock to UART1
  SYSCTL_RCGCUART_R |= 0x2;

  //wait for GPIOB and UART1 peripherals to be ready
  while ((SYSCTL_PRGPIO_R & 0x2) == 0) {};
  while ((SYSCTL_PRUART_R & 0x2) == 0) {};

  //enable alternate functions on port B pins
  GPIO_PORTB_AFSEL_R |= 0x3;

  //enable digital functionality on port B pins
  GPIO_PORTB_DEN_R |= 0x3;

  //enable UART1 Rx and Tx on port B pins
  GPIO_PORTB_PCTL_R &= 0xFFFFFF00;     // Force 0's in the desired locations
  GPIO_PORTB_PCTL_R |= 0x11;     // Force 1's in the desired locations

  //calculate baud rate
  float BRD = 16000000.0 / (16.0 * 115200.0);
  uint16_t iBRD = (int)(BRD); //use equations
  uint16_t fBRD = (int)((BRD - (int)(BRD)) * 64 + 0.5); //use equations

  //turn off UART1 while setting it up
  UART1_CTL_R &= 0xFFFFFFF0;

  //set baud rate
  //note: to take effect, there must be a write to LCRH after these assignments
  UART1_IBRD_R = iBRD;
  UART1_FBRD_R = fBRD;

  //set frame, 8 data bits, 1 stop bit, no parity, no FIFO
  //note: this write to LCRH must be after the BRD assignments
  UART1_LCRH_R = 0x60;

  //use system clock as source
  //note from the datasheet UARTCCC register description:
  //field is 0 (system clock) by default on reset
  //Good to be explicit in your code
  UART1_CC_R = 0x0;

  //re-enable UART1 and also enable RX, TX (three bits)
  //note from the datasheet UARTCTL register description:
  //RX and TX are enabled by default on reset
  //Good to be explicit in your code
  //Be careful to not clear RX and TX enable bits
  //(either preserve if already set or set them)
  UART1_CTL_R |= 0x301;

}

void uart_sendChar(char data){
	while(UART1_FR_R & 0x20){}

	//send data
	UART1_DR_R = data;
}

char uart_receive(void){
	char data = 0;

	//wait to receive
	while(UART1_FR_R & UART_FR_RXFE){}

	data = (char)(UART1_DR_R & 0xFF);

	return data;
}

void uart_sendStr(const char *data){
    while(*data != '\0')
        {
            uart_sendChar(*data);
            data++;
        }
}
