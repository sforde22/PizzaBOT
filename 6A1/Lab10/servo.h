/*
 * servo.h
 *
 *  Created on: Apr 7, 2024
 *      Author: ncelsi
 */

#ifndef SERVO_H_
#define SERVO_H_

#include <stdint.h>
#include <stdbool.h>
#include <inc/tm4c123gh6pm.h>


//extern volatile unsigned long FIN_TIME;

void servo_init(void);

void servo_move(uint16_t degrees);


#endif /* SERVO_H_ */
