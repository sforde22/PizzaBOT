/**
 * lab5_template.c
 *
 * Template file for CprE 288 Lab 5
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 *
 * @author Phillip Jones, updated 6/4/2019
 * @author Diane Rover, updated 2/25/2021, 2/17/2022
 */

#include "button.h"
#include "timer.h"
#include "lcd.h"

#include "uart.h"  // Functions for communicating between CyBot and Putty (via UART1)
                         // PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity, COM1
#include "cyBot_uart.h"

#include "cyBot_Scan.h"  // Scan using CyBot servo and sensors


//#warning "Possible unimplemented functions"
//#define REPLACEME 0



int main(void) {
	button_init();
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();

//  // initialize the cyBot UART1 before trying to use it
//
//  // (Uncomment ME for UART init part of lab)
//	cyBot_uart_init_clean();  // Clean UART1 initialization, before running your UART1 GPIO init code
//
//	// Complete this code for configuring the GPIO PORTB part of UART1 initialization (your UART1 GPIO init code)
//    SYSCTL_RCGCGPIO_R |= 0x2;
//	 while ((SYSCTL_PRGPIO_R & 0x2) == 0) {};
//	 GPIO_PORTB_DEN_R |= 0x3;
//	 GPIO_PORTB_AFSEL_R |= 0x3;
//     GPIO_PORTB_PCTL_R &= 0xFFFFFF00;     // Force 0's in the desired locations
//     GPIO_PORTB_PCTL_R |= 0x11;     // Force 1's in the desired locations
//		 // Or see the notes for a coding alternative to assign a value to the PCTL field
//
//    // (Uncomment ME for UART init part of lab)
//	 cyBot_uart_init_last_half();  // Complete the UART device configuration
	uart_init();
	 // Initialize the scan

	 cyBOT_init_Scan(0b0011);
	 // Remember servo calibration function and variables from Lab 3

	 char string[21];
	 int i;
	 char data;
	 while(1){
	     string[0] = '\0';
	     while(strlen(string) < 20){
	         data = uart_receive();
	         if(data == '\r'){
	             break;
	         }
	         i = strlen(string);
	         string[i] = data;
	         string[i+1] = '\0';
	         lcd_clear();
	         lcd_home();
	         lcd_printf("%s\n%d", string, i+1);
	         uart_sendStr(string);
	         uart_sendStr("\r\n");
	     }
	     lcd_clear();
	     lcd_home();
	     lcd_printf("%s", string);
	 }

}
