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

#include "timer.h"
#include "lcd.h"
#include "movement.h"
#include "uart.h"

#include "cyBot_uart.h"  // Functions for communicating between CyBot and Putty (via UART1)
                         // PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity, COM1
#include "cyBot_Scan.h"  // Scan using CyBot servo and sensors
//#include "uart.h"


//#warning "Possible unimplemented functions"
#define REPLACEME 0



int main(void) {
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	char arr[21];
	char x;
	int i  =0;
	int i_arr[3];
  // initialize the cyBot UART1 before trying to use it

  //(Uncomment ME for UART init part of lab)
	 cyBot_uart_init_clean();  // Clean UART1 initialization, before running your UART1 GPIO init code

	// Complete this code for configuring the GPIO PORTB part of UART1 initialization (your UART1 GPIO init code)
     SYSCTL_RCGCGPIO_R |= 0x02;
	   while ((SYSCTL_PRGPIO_R & 0x02) == 0) {};
		  GPIO_PORTB_DEN_R |= 0x03;
		  GPIO_PORTB_AFSEL_R |= 0x03;
     GPIO_PORTB_PCTL_R &= 0x00000011;     // Force 0's in the desired locations
     GPIO_PORTB_PCTL_R |= 0x00000011;     // Force 1's in the desired locations
		 // Or see the notes for a coding alternative to assign a value to the PCTL field

    // (Uncomment ME for UART init part of lab)
		 cyBot_uart_init_last_half();  // Complete the UART device configuration

		// Initialize the scan
	   cyBOT_init_Scan(0b0011);
		// Remember servo calibration function and variables from Lab 3

	// YOUR CODE HERE

while(i < 20)
	{
    x = uart_receive();
    if(x == '\r') {
                break;
            }
    else {
        arr[i] = x;

        i++;
    }



	}
lcd_puts(arr);
lcd_gotoLine(2);
sprintf(i_arr,"%d",i);
lcd_puts(i_arr);
uart_sendStr(arr);
uart_sendChar('\n');
uart_sendChar('\r');
uart_sendStr(i_arr);

}
