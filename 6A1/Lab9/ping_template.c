/**
 * Driver for ping sensor
 * @file ping.c
 * @author
 */

#include "ping_template.h"
#include "Timer.h"
#include "lcd.h"

volatile unsigned long START_TIME = 0;
volatile unsigned long END_TIME = 0;
volatile enum{LOW, HIGH, DONE} STATE = LOW; // State of ping echo pulse

volatile int data;
volatile unsigned short ping_flag;
volatile unsigned short scan_flag;
int started = 0;
int scuffed = 0;
volatile unsigned long END_TIME;
volatile unsigned long START_TIME;

void ping_init (void){

    // YOUR CODE HERE
    SYSCTL_RCGCGPIO_R |= 0x02;

    SYSCTL_RCGCTIMER_R |= 0x8;

    while ((SYSCTL_PRGPIO_R & 0x02) == 0) {};
    while ((SYSCTL_RCGCGPIO_R & 0x08) == 0) {};
//    GPIO_PORTB_DIR_R |= 0x3;
    GPIO_PORTB_DEN_R |= 0x08;
    GPIO_PORTB_AFSEL_R |= 0x08;
    GPIO_PORTB_PCTL_R = 0x00007000; // Need to enable pin 7
    //enable digital functionality on port B pins

    //enable alternate functions on port B pins


//    TIMER3_ICR_R |= 0x400;
//    TIMER3_IMR_R |= 0x400;





    TIMER3_CTL_R &= 0xEFF; //disable Timer 3b while setting up

//    TIMER3_CFG_R &= 0x0;
    TIMER3_CFG_R |= 0x4;

    TIMER3_TBMR_R |= 0x7; //0x17
    TIMER3_TBMR_R &= ~0x10; //0x17


    TIMER3_CTL_R |= 0xC00;

    TIMER3_TBPR_R = 0xFF;
    TIMER3_TBILR_R |= 0xFFFF;

    TIMER3_IMR_R |= 0x400;
    TIMER3_ICR_R |= 0x400;
    TIMER3_CTL_R |= 0x100;

    NVIC_EN1_R |= 0x0010;
    NVIC_PRI1_R = (NVIC_PRI1_R & 0xFF0FFFFF) | 0x00200000;

    IntRegister(INT_TIMER3B, TIMER3B_Handler);
    IntMasterEnable();

    // Might neet TBR register ot TBV

}

void ping_trigger (void){

    STATE = LOW;
    TIMER3_CTL_R &= ~0x100;
    TIMER3_IMR_R &= ~0x400;
    GPIO_PORTB_AFSEL_R &= 0xF7;

    GPIO_PORTB_DIR_R |= 0x8;
    GPIO_PORTB_DATA_R &= ~0x8;
    timer_waitMicros(5);
    GPIO_PORTB_DATA_R |= 0x8;
    timer_waitMicros(10);
    GPIO_PORTB_DATA_R &= ~0x8;
    GPIO_PORTB_DIR_R &= ~0x8;

//    GPIO_PORTB_DIR_R &= ~0x8;

    TIMER3_ICR_R |= 0x400;

    GPIO_PORTB_AFSEL_R |= 0x8;

    TIMER3_IMR_R |= 0x400;
    TIMER3_CTL_R |= 0x100;
}
void TIMER3B_Handler(void){
//    if (TIMER3_RIS_R & 0x400) {
//int count = 0;
//        count++;
//        lcd_printf("%d", count);
            // Clear the interrupt flag

            // Check if the pulse is just started
            if (STATE == LOW) {
                // Record the start time
                START_TIME = TIMER3_TBR_R;
                // Move to the next state
                STATE = HIGH;
            } else if (STATE == HIGH) {
                // Record the end time
                END_TIME = TIMER3_TBR_R;
                // Move to the next state
                STATE = DONE;

                // Set ping_flag to indicate that the measurement is done
                ping_flag = 1;
            }
            TIMER3_ICR_R |= 0x400;
//        }
}


//  if(TIMER3_RIS_R & 0x400){
//
//      if(started == 1){
////          if(END_TIME < TIMER3_TBR_R){
////              END_TIME = -1;
////          }
////          else{
//              END_TIME = END_TIME - TIMER3_TBR_R;
////              STATE = HIGH;
////          }
//          ping_flag = 1;
//          TIMER3_ICR_R |= 0x400;
//          scuffed = 1;
//          started = 0;
//          STATE = DONE;
//      }
//
//      else{
//          started = 1;
////          STATE = LOW;
//          END_TIME = TIMER3_TBR_R;
//          START_TIME = TIMER3_TBR_R;
//          TIMER3_ICR_R |= 0x400;
//      }

  // YOUR CODE HERE
  // As needed, go back to review your interrupt handler code for the UART lab.
  // What are the first lines of code in the ISR? Regardless of the device, interrupt handling
  // includes checking the source of the interrupt and clearing the interrupt status bit.
  // Checking the source: test the MIS bit in the MIS register (is the ISR executing
  // because the input capture event happened and interrupts were enabled for that event?
  // Clearing the interrupt: set the ICR bit (so that same event doesn't trigger another interrupt)
  // The rest of the code in the ISR depends on actions needed when the event happens.



float ping_getDistance (void){


//     YOUR CODE HERE


    ping_trigger();
    while(STATE != DONE) {};

    float timeDif = 0;
    int overflow = (END_TIME > START_TIME);
    timeDif = ((unsigned long) overflow << 24) + START_TIME - END_TIME;
    float dist = timeDif / 1000;

//    dist = (timeDif/2)*343*100;

    lcd_printf("%.2f %d",dist, overflow);


    STATE = LOW;
    return dist;

}

//
//
//if(scan_flag == 1){
//           scan_flag = 0;
//       }
//
//       while(ping_flag != 1){
//           if(ping_flag != 1) ping_trigger();
//           timer_waitMillis(1000);
//       }
//
//       ping_flag = 0;
//       sprintf(str, "Overflow: %s\nData: %d", data < 0 ? "yes" : "no", data);
//
//       lcd_printf(str);


