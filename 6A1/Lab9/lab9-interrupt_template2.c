/**
 * lab4_template.c
 *
 * Template file for CprE 288 lab 4
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 */


#include "Timer.h"
#include "lcd.h"
#include "uart-interrupt.h"
#include "cyBot_Scan.h"
#include <stdlib.h>
#include "movement.h"
#include "open_interface.h"
int END_IR_ARR_VALUE = -1;
//start_flag = 0;

// 238000, 1225000
int avgArr(int *arr);

struct object
{
    int startAngle;
    int endAngle;
    float dist;
};
int main(void)
{
    right_calibration_value = 301000;
    left_calibration_value = 1319500;
    timer_init(); // Must be called before lcd_init(), which uses timer functions

    lcd_init();
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    uart_interrupt_init();
    cyBOT_init_Scan(0b0111);

    // Don't forget to initialize the cyBot UART before trying to use it
   char i_arr[2];
   char angle_arr[10];
   double fin_angle;
    // YOUR CODE HERE
    int i;
    //    float M_PI = 3.1416;

    while (1)
    {
        if (start_flag)
        {
            start_flag = 0;
            int objStarted = 0;
            int objWidth = 0;
            int objId = 0;
            int smallestWidth = 10000;
            int smallestAngle = 360;
            float smallestDist = 0;
            cyBOT_Scan_t scanData;
            struct object obj;
            for (i = 0; i <= 180; i += 2)
            {
//                sprintf(i_arr, "%d", i);
//                uart_sendStr(i_arr);
//                uart_sendChar('\n');
//                uart_sendChar('\r');
                int sensorArr[4];
                int j;
                for (j = 0; j < 3; j++)
                {
                    cyBOT_Scan(i, &scanData);

                    sensorArr[j] = scanData.IR_raw_val;
                }

                sensorArr[3] = END_IR_ARR_VALUE;
                int averageIR_Sensor = avgArr(sensorArr);

                if (averageIR_Sensor > 700)
                {
                    if (!objStarted)
                    {
                        objStarted = 1;
                        obj.startAngle = i;
                        objWidth = 1;
                        objId++;
                    }
                    else
                    {
                        objWidth++;
                    }
                }
                else if (objStarted)
                {
                    objStarted = 0;
                    if (objWidth > 3)
                    {
                        obj.endAngle = i;
                        float angularWidth = (obj.endAngle - obj.startAngle) / 2;
                        float midpoint = (obj.endAngle + obj.startAngle) / 2;
                        cyBOT_Scan(midpoint, &scanData);
                        obj.dist = scanData.sound_dist;
                        float width = 2 * M_PI * obj.dist * (angularWidth / 360.0);
                        if (width < smallestWidth)
                        {
                            smallestWidth = width;
                            smallestAngle = midpoint;
                            smallestDist = obj.dist;
                        }
                        char dataStr[50];
                        sprintf(dataStr, "object: %d width: %f distance: %.2f\n\r", objId, width, obj.dist);
                        uart_sendStr(dataStr);
                        obj.startAngle = 0;
                        obj.endAngle = 0;
                        objWidth = 0;
                    }
                    else
                    {
                        objId--;
                    }
                }

                //                char dataStr[20];
                //                sprintf(dataStr, "%d, %.2f\n\r", averageIR_Sensor, scanData.sound_dist);
                //                uart_sendStr(dataStr);
                //                lcd_printf(dataStr);
            }
            objStarted = 0;
            if (objWidth > 5)
            {
                obj.endAngle = i;
                float angularWidth = (obj.endAngle - obj.startAngle) / 2;
                float midpoint = (obj.endAngle + obj.startAngle) / 2;
                cyBOT_Scan(midpoint, &scanData);
                obj.dist = scanData.sound_dist;
                float width = 2 * 3.14159 * obj.dist * (angularWidth / 360.0);
                if (width < smallestWidth)
                {
                    smallestWidth = width;
                    smallestAngle = midpoint;
                    smallestDist = obj.dist;
                }
                char dataStr[50];
                sprintf(dataStr, "object: %d width: %f distance: %.2f\n\r", objId, width, obj.dist);
                uart_sendStr(dataStr);
                obj.startAngle = 0;
                obj.endAngle = 0;
                objWidth = 0;
            }
            else
            {
                objId--;
            }
            if(smallestAngle <= 90)
                {
                  //MOVE TO THE RIGHT
                                    //PUT BUMP DETECTION HERE
                                    fin_angle = 90.0 - smallestAngle;
                                    sprintf(angle_arr, "%f", fin_angle);
                                    uart_sendStr(angle_arr);
                                    uart_sendChar('\n');
                                    uart_sendChar('\r');
                                    turn_right(sensor_data, fin_angle);
                                    collision_setection(sensor_data, smallestDist);


                                }
                                else if(smallestAngle > 90)
                                {
                                    // MOVE TO THE LEFT
                                    //PUT BUMP DETECTION HERE
                                    fin_angle = 180 - smallestAngle;
                                    sprintf(angle_arr, "%f", fin_angle);
                                    uart_sendStr(angle_arr);
                                    uart_sendChar('\n');
                                    uart_sendChar('\r');
                                    turn_left(sensor_data, fin_angle - 10);
                                    collision_setection(sensor_data, smallestDist);


                                }





                oi_free(sensor_data);

        //        cyBOT_Scan_t* scanData = malloc(sizeof(cyBOT_SERVRO_cal_t));
    }
}
}

int avgArr(int *arr)
{
    int total = 0;
    int i = 0;
    while (arr[i] != END_IR_ARR_VALUE)
    {
        total += *arr;
        i++;
    }

    return total / 3;
}
