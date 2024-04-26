/*
 * adc.c
 *
 *  Created on: Mar 19, 2024
 *      Author: sforde22
 */

#include "adc.h"

const int lookupdist[22][2] = { {1123, 50}, {1136, 48}, {1144, 46}, {1158, 44}, {1186, 42}, {1217, 40}, {1263, 38}, {1287, 36}, {1309, 34}, {1350, 32}, {1384, 30}, {1434, 28}, {1497, 26}, {1564, 24}, {1664, 22}, {1762, 20}, {1868, 18}, {2000, 16}, {2173, 14}, {2437, 12}, {2800, 10}, {3120, 9} };

void adc_init(void){
    SYSCTL_RCGCADC_R |= 0x0001;   // 1) activate ADC0
    SYSCTL_RCGCGPIO_R |= 0x2;    // 2) activate clock for Port E
    while((SYSCTL_PRGPIO_R&0x2) != 0x2){};  // 3 for stabilization
    GPIO_PORTB_DIR_R &= ~0x10;    // 4) make PE4 input
    GPIO_PORTB_AFSEL_R |= 0x10;   // 5) enable alternate function on PE4
    GPIO_PORTB_DEN_R &= ~0x10;    // 6) disable digital I/O on PE4
    GPIO_PORTB_AMSEL_R |= 0x10;   // 7) enable analog functionality on PE4
  // while((SYSCTL_PRADC_R&0x0001) != 0x0001){}; // good code, but not implemented in simulator
    ADC0_PC_R &= ~0xF;
    ADC0_PC_R |= 0x1;             // 8) configure for 125K samples/sec
    ADC0_SSPRI_R = 0x0123;        // 9) Sequencer 3 is highest priority
    ADC0_ACTSS_R &= ~0x0008;      // 10) disable sample sequencer 3
    ADC0_EMUX_R &= ~0xF000;       // 11) seq3 is software trigger
    ADC0_SSMUX3_R &= ~0x000F;
    ADC0_SSMUX3_R += 10;           // 12) set channel
    ADC0_SSCTL3_R = 0x0006;       // 13) no TS0 D0, yes IE0 END0
    ADC0_IM_R &= ~0x0008;         // 14) disable SS3 interrupts
    ADC0_ACTSS_R |= 0x0008;       // 15) enable sample sequencer 3
    //ADC0_SAC_R |= ADC_SAC_AVG_16X;
}

//------------ADC0_InSeq3------------

// Busy-wait analog to digital conversion

// Input: none

// Output: 12-bit result of ADC conversion

int adc_get(void){
    int result;
    ADC0_PSSI_R = 0x0008;            // 1) initiate SS3
    while((ADC0_RIS_R&0x08)==0){};   // 2) wait for conversion done
    result = ADC0_SSFIFO3_R&0xFFF;   // 3) read result
    ADC0_ISC_R = 0x0008;             // 4) acknowledge completion
    return result;
}

//when called returns the distance based on the sensor
int adc_dist(void){
    int adcval = adc_get();
    int lookuploc;
    int i;
    double adcdist = ((305.0 * exp((-adcval)/535.0)) + 8.5);
//    for(i = 0; i < sizeof(lookupdist); i++){
//        if(lookupdist[i][0] > adcval){
//            lookuploc = i;
//            i = sizeof(lookupdist);
//        }
//    }
//    int adcdist = lookupdist[lookuploc][1];
    return (int)adcdist;
}
