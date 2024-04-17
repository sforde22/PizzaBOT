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


int main (void) {

	timer_init(); // Initialize Timer, needed before any LCD screen functions can be called 
	              // and enables time functions (e.g. timer_waitMillis)

	lcd_init();   // Initialize the LCD screen.  This also clears the screen. 

	// Print "Hello, world" on the LCD
	//lcd_printf("Hello, world");
	//lcd_puts("Hello world");
	while(1){
	    char message[] = "Microcontrollers are lots of fun!                    ";
	    char banner[]  = "                    ";
	    int i,j;

	    for(j=0;j<53;++j){
	        //left shift
	    for(i=1; i < 21; ++i) {
	        banner[i-1] = banner[i];
	    }
	    //takes the current char in message and puts it into the last slot in banner
	    banner[19] = message[j];
	    timer_waitMillis(300);
	    lcd_init();
	    lcd_printf(banner);


	}
	}
	// lcd_puts("Hello, world"); // Replace lcd_printf with lcd_puts
        // step through in debug mode and explain to TA how it works
    
	// NOTE: It is recommended that you use only lcd_init(), lcd_printf(), lcd_putc, and lcd_puts from lcd.h.
       // NOTE: For time functions, see Timer.h

	return 0;
}
