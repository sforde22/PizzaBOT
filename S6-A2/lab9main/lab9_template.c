/**
 * @file lab9_template.c
 * @author
 * Template file for CprE 288 Lab 9
 */

#include "Timer.h"
#include "lcd.h"
#include "ping.h"

// Uncomment or add any include directives that are needed

int main(void) {
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	ping_init();

	// YOUR CODE HERE

	while(1)
	{
	    ping_trigger();
	    timer_waitMillis(1);
	    float i = ping_getDistance();
	    lcd_printf("%f, %d", i, overflow);
	    timer_waitMillis(500);

	}

}
