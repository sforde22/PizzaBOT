/**
 * Driver for servo
 * Also, 16MHz system clock with a period of 20ms should be 320,000(0x4E200) clock periods
 * @file servo.c
 * @author Samuel Forde
 */

#include <servo.h>
#include "Timer.h"

int prevdeg = 90;

void servo_init (void){
	
	//gpio
	SYSCTL_RCGCGPIO_R |= 0x2;
	while ((SYSCTL_PRGPIO_R & 0x2) == 0) {};
	GPIO_PORTB_DIR_R |= 0x20;
	GPIO_PORTB_AFSEL_R |= 0x20;
	GPIO_PORTB_DEN_R |= 0x20;
	
	//timer start
	SYSCTL_RCGCTIMER_R |= 0x2;
	while((SYSCTL_PRTIMER_R & 0x2) == 0) {};
	GPIO_PORTB_PCTL_R |= 0x700000;
	TIMER1_CFG_R |= 0x4;
	
	TIMER1_TBMR_R &= ~0x4;
	TIMER1_TBMR_R |= 0xA;
	//signal state control
	TIMER1_CTL_R &= ~0x4000;

	//prescaler+normal timer
	TIMER1_TBILR_R = 0x4E200 & 0xFFFF;
	TIMER1_TBPR_R = 0x4E200>>16;

	TIMER1_CTL_R &= ~0x100;
}

void servo_move(uint16_t degrees){
    float ms = ((float)degrees / 180.0) + 1.0;
    int match = (int)(ms * 16000.0);
	match = 320000 - match;

	//falling edge/match reg
	TIMER1_TBPMR_R = match>>16;
	TIMER1_TBMATCHR_R = match & 0xFFFF;
	TIMER1_CTL_R |= 0x100;
	timer_waitMillis(1000);
	TIMER1_CTL_R &= ~0x100;
}
