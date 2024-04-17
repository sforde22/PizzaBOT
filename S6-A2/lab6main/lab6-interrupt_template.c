/**
 * lab6-interrupt_template.c
 *
 * Template file for CprE 288 Lab 6
 *
 * @author Diane Rover, 2/15/2020
 *
 */

#include "open_interface.h"
#include "movement.h"
#include "lcd.h"
#include "cyBot_Scan.h"
#include "Timer.h"
#include "uart-interrupt.h"

// Uncomment or add any include directives that you want to use
// #include "open_interface.h"
// #include "movement.h"
// #include "button.h"

// Your code can use the global variables defined in uart-interrupt.c
// They are declared with the extern qualifier in uart-interrupt.h, which makes the variables visible to this file.



int main(void) {
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	//uart_interrupt_init();
	uart_interrupt_init();
    cyBOT_init_Scan(0b11);

	// OPTIONAL
	//assign a value to command_byte if you want to know whether that ASCII code is received
	//note that command_byte is global shared variable read by the ISR
	//for example, try using a tab character as a command from PuTTY
    int i = 0;
    cyBOT_Scan_t* scan_data;
    while(1)
	{
        if(command_flag == 0){
            if(i >= 180){
                i = 0;
            }
            scan_data = calloc(1, sizeof(cyBOT_Scan_t));
            cyBOT_Scan(i, scan_data);
            i += 3;

            //uart_sendStr(sprintf("%d", i));
//                 OPTIONAL
//                test and reset command_flag if your ISR is updating it
//                for example, if the flag is 1, do something, like send a message to PuTTY or LCD, or stop a sensor scan, etc.
//                be sure to reset command_flag so you don't keep responding to an old flag
        }
            free(scan_data);

	}

}
