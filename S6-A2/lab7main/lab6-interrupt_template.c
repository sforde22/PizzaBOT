/**
 * lab6-interrupt_template.c
 *
 * Template file for CprE 288 Lab 6
 *
 * @author Diane Rover, 2/15/2020
 *
 */

#include "open_interface.h"
#include "movement.h"
#include "lcd.h"
#include "cyBot_Scan.h"
#include "Timer.h"
#include "uart-interrupt.h"
#include <math.h>

// Uncomment or add any include directives that you want to use
// #include "open_interface.h"
// #include "movement.h"
// #include "button.h"

// Your code can use the global variables defined in uart-interrupt.c
// They are declared with the extern qualifier in uart-interrupt.h, which makes the variables visible to this file.


const int maxDist = 900;

int main(void) {
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	uart_interrupt_init();
    cyBOT_init_Scan(0b111);


    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);


    //cybot 15
    right_calibration_value = 253750;
    left_calibration_value = 1272250;

    int i = 0;
    cyBOT_Scan_t* scan_data;

//    cyBOT_SERVO_cal();
    int sumAvg = 0;
    int arrayCounter = 1;
    char out[25];
    int dist = 0;

    int anglestart[10];
    int angleend[10];
    int targetAngle = 100;
    int THESMALLEST = 500;

//    anglestart = (int *) malloc(sizeof(*anglestart) * 10);
//    angleend = (int *) malloc(sizeof(*angleend) * 10);
    while(command_flag == 1){ }

    scan_data = calloc(1, sizeof(cyBOT_Scan_t));

    for(i = 0; i < 170; i+=3){
        sumAvg = cyBOT_Scan_Avg(i, scan_data);

        sprintf(out, "Angle: %d, IR Val: %d\r\n", i, sumAvg);
        uart_sendStr(out);

        //Found object
        if(sumAvg > maxDist) {
            anglestart[arrayCounter] = i;
            //do the scanning in here until object ends
            while(sumAvg > maxDist && i < 170){
                sumAvg = 0;
                i += 3;
                sumAvg = cyBOT_Scan_Avg(i, scan_data);
                sprintf(out, "Angle: %d, IR Val: %d\r\n", i, sumAvg);
                uart_sendStr(out);
            }
            angleend[arrayCounter] = i;

            if(angleend[arrayCounter] - anglestart[arrayCounter] == 3){
                arrayCounter--;
            }

            arrayCounter++;
        }
        sumAvg = 0;
    }
    //int targetAngle = 0;
    for(i = 1; i < arrayCounter; i++){
        sumAvg = (anglestart[i] + angleend[i])/2;
        dist = cyBOT_Scan_Dist(sumAvg, scan_data);

        if(dist < 100 && sumAvg > 7){
            sprintf(out, "Object %d At %d degrees %d cm\r\n", i, sumAvg, dist);
            uart_sendStr(out);

            float theta = (float)angleend[i] - (float)anglestart[i];
            dist = 2*((float)dist*tan(((theta/2.0) * 3.14 / 180.0)));

            if(dist < THESMALLEST){
                THESMALLEST = dist;
                targetAngle = (angleend[i] + anglestart[i])/2;
            }

            sprintf(out, "Angular Width = %d Linear Width = %d\r\n", angleend[i] - anglestart[i], dist);
            uart_sendStr(out);
        }
    }

    sprintf(out, "Smallest Width at %d degrees, %d cm\r\n", targetAngle, THESMALLEST);
    uart_sendStr(out);

    oi_init(sensor_data);
    sensor_data = oi_alloc();

    if(targetAngle < 90){
        turn_right(sensor_data, 90 - targetAngle);
    }
    if(targetAngle > 90){
        turn_left(sensor_data, targetAngle - 90);
    }
    moveWithBumps(sensor_data, THESMALLEST * 100);

    free(scan_data);
    oi_free(sensor_data);
}

int cyBOT_Scan_Avg(int angle, cyBOT_Scan_t* getScan){
    int sumAvg = 0;
    int i = 0;

    for(i = 0; i < 3; i++){
        cyBOT_Scan(angle, getScan);
        sumAvg += getScan->IR_raw_val;
    }

    sumAvg = sumAvg/3;
    return sumAvg;
}

int cyBOT_Scan_Dist(int angle, cyBOT_Scan_t* getScan){
    int sumAvg = 0;
    int i = 0;

    for(i = 0; i < 3; i++){
        cyBOT_Scan(angle, getScan);
        sumAvg += (int)getScan->sound_dist;
    }
    sumAvg = sumAvg/3;
    return sumAvg;
}

