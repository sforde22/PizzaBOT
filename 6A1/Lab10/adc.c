/*
 * adc.c
 *
 *  Created on: Mar 19, 2024
 *      Author: ncelsi
 */

#include "adc.h"
#include <inc/tm4c123gh6pm.h>
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/interrupt.h"


void adc_init(void)
{
    SYSCTL_RCGCADC_R |= 0x0001; // Activate ADC0
        SYSCTL_RCGCGPIO_R |= 0x02;  // Activate clock for Port B

        while((SYSCTL_PRADC_R & 0x0001) != 0x0001); // Wait for ADC0 to become ready

        GPIO_PORTB_DIR_R &= ~0x10; // Make PB4 input
        GPIO_PORTB_AFSEL_R |= 0x10; // Enable alternate function on PB4
        GPIO_PORTB_DEN_R &= ~0x10; // Disable digital I/O on PB4
        GPIO_PORTB_AMSEL_R |= 0x10; // Enable analog functionality on PB4

        ADC0_PC_R &= ~0xF; // Clear bits 3:0 for default maximum speed
        ADC0_PC_R |= 0x1; // Configure for 125K samples/sec
        ADC0_SSPRI_R = 0x0123; // Sequencer 3 is highest priority
        ADC0_ACTSS_R &= ~0x0008; // Disable sample sequencer 3
        ADC0_EMUX_R &= ~0xF000; // Seq3 is software trigger
        ADC0_SSMUX3_R &= ~0x000F; // Clear SS3 field
        ADC0_SSMUX3_R += 10; // Set channel to 10 (corresponding to PB4)
        ADC0_SSCTL3_R = 0x0006; // No TS0 D0, yes IE0 END0
        ADC0_IM_R &= ~0x0008; // Disable SS3 interrupts
        ADC0_ACTSS_R |= 0x0008; // Enable sample sequencer 3


}

uint16_t adc_read(void)
{
       ADC0_PSSI_R |= 0x0008;          // Start a conversion for SS3
       while((ADC0_RIS_R & 0x08) == 0); // Wait for conversion to complete
       uint16_t result = ADC0_SSFIFO3_R; // Read the ADC result
       ADC0_ISC_R = 0x0008;             // Clear SS3 interrupt flag
       return result;                 // Return the ADC result
}



