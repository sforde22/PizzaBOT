/// Simple 'Hello, world' program
/**
 * This program prints "Hello, world" to the LCD screen
 * @author Chad Nelson
 * @date 06/26/2012
 *
 * updated: phjones 9/3/2019
 * Description: Added timer_init call, and including Timer.h
 */

#include "Timer.h"
#include "lcd.h"
#include "open_interface.h"
#include "uart-interrupt.h"
#include "movement.h"
#include "cyBot_Scan.h"


int main (void) {
    
    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
    oi_init(sensor_data); // do this only once at start of main()
    uart_interrupt_init(); //Initialize the Interrupt
    lcd_init(); //Initialize the lcd
    cyBOT_Scan_t* scanData; //Declare the scanData
    cyBOT_init_Scan(0b0111); //Initailize the ....








    oi_free(sensor_data); // do this once at end of main()
	return 0;
}

