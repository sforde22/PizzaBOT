/*
 * servo.c
 *
 *  Created on: Apr 7, 2024
 *      Author: ncelsi
 */

#include "servo.h"
#include "Timer.h"
#include "lcd.h"

double MILLIS;
long CLK;
//volatile unsigned long FIN_TIME;

char arr[15];

void servo_init(void) {
        SYSCTL_RCGCGPIO_R |= 0x02;

        SYSCTL_RCGCTIMER_R |= 0x02;

        while ((SYSCTL_PRGPIO_R & 0x02) == 0) {};
        while ((SYSCTL_RCGCGPIO_R & 0x02) == 0) {};
        GPIO_PORTB_DIR_R |= 0x20;
        GPIO_PORTB_DEN_R |= 0x20;
        GPIO_PORTB_AFSEL_R |= 0x20;
        GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0x0FFFFF) | 0x700000; // Need to enable pin 7
        //enable digital functionality on port B pins

        //enable alternate functions on port B pins

        TIMER1_CTL_R &= 0xEFF; //disable Timer 1b while setting up

    //    TIMER3_CFG_R &= 0x0;
        TIMER1_CFG_R |= 0x4;

        TIMER1_TBMR_R |= 0xA;
        TIMER1_TBMR_R &= ~0x5; //count down


//        TIMER1_CTL_R |= 0x000; //inversion = no

        TIMER1_TBPR_R = 0x4;
        TIMER1_TBILR_R = 0xE200;

        TIMER1_CTL_R |= 0x100;
}

void servo_move(uint16_t degrees) {
    MILLIS = (degrees / 180.0) + 1;
    CLK = MILLIS * 16000;

    CLK = 0x4E200 - CLK; //4E200 is 20 milliseconds

    TIMER1_TBPMR_R = CLK >> 16;

    TIMER1_TBMATCHR_R = CLK & 0xFFFF;



}
