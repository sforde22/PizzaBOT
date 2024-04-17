/**
 * @file lab9_template.c
 * @author
 * Template file for CprE 288 Lab 9
 */

#include "Timer.h"
#include "lcd.h"
#include "servo.h"

// Uncomment or add any include directives that are needed

#warning "Possible unimplemented functions"
#define REPLACEME 0

int main(void) {
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	servo_init();

	while(1)
	{

	servo_move(30);
	timer_waitMillis(1000);
	servo_move(159);
	timer_waitMillis(1000);
	servo_move(0);
	timer_waitMillis(1000);
	servo_move(90);
	break;


	//break;
	// YOUR CODE HERE
	}


}
