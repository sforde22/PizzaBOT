/**
 * Driver for servo
 * @file servo.c
 * @author Samuel Forde
 */
#ifndef SERVO_H_
#define SERVO_H_

#include <stdint.h>
#include <stdbool.h>
#include <inc/tm4c123gh6pm.h>

extern volatile unsigned long START_TIME;
extern volatile unsigned long END_TIME;
//extern volatile enum{LOW, HIGH, DONE} STATE;
extern volatile int TESTER;
extern int overflow;

/**
 * Initialize servo. Uses PB5 and Timer 1B
 */
void servo_init (void);

/**
 * Moves the sensor the given degrees
 */
void servo_move(uint16_t degrees);

#endif /* SERVO_H_ */
