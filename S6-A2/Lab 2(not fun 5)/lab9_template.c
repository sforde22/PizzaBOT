/**
 * @file lab9_template.c
 * @author
 * Template file for CprE 288 Lab 9
 */

#include "Timer.h"
#include "lcd.h"
#include "ping.h"
#include "servo.h"

// Uncomment or add any include directives that are needed

int main(void) {
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	ping_init();

	// YOUR CODE HERE
	servo_init();
	servo_move(90);
	servo_move(30);
	servo_move(150);
	servo_move(90);
//	while(1)
//	{
//
//	}

}
