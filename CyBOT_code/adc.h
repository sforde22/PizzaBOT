/*
 * adc.h
 *
 *  Created on: Mar 19, 2024
 *      Author: sforde22
 */

#ifndef ADC_H_
#define ADC_H_

#include <inc/tm4c123gh6pm.h>
#include <stdint.h>
#include <math.h>

void adc_init(void);

int adc_get(void);

int adc_dist(void);

#endif /* ADC_H_ */
