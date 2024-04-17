/*
 * movement.c
 *
 *  Created on: Jan 30, 2024
 *      Author: joshs1
 */

//#include "open_interface.c"
#include "open_interface.h"
#include <string.h>
#include "cyBot_uart.h"
#include "cyBot_Scan.h"
#include "uart-interrupt.h"

const float PI = 3.14159265358;

double move_forward (oi_t *sensor_data, double distance_mm)
{
       // the following code could be put in function move_forward()

       double sum = 0; // distance member in oi_t struct is type double
       oi_setWheels(500,500); //move forward at full speed

       while (sum < distance_mm) {
           oi_update(sensor_data);
           sum += sensor_data -> distance; // use -> notation since pointer

           char buf[128];
           sprintf(buf, "%f", sum);

           lcd_printf(buf);


       }
       return 0;
}


double move_back (oi_t *sensor_data, double distance_mm)
{
       // the following code could be put in function move_forward()

       double sum = distance_mm; // distance member in oi_t struct is type double
       oi_setWheels(-250,-250); //move forward at full speed

       while (sum > 0) {
           oi_update(sensor_data);
           sum += sensor_data -> distance; // use -> notation since pointer
       }

       oi_setWheels(0,0);

       return 0;
}

double turn_right(oi_t *sensor, double degrees)
{
    double sum = 90;
    oi_setWheels(0,500);

    while(sum > 10)
    {
        oi_update(sensor);
        sum += sensor->angle;
    }
    oi_setWheels(0,0);



    return 0;
}

double turn_left(oi_t *sensor, double degrees)
{

    double sum = 0;
        oi_setWheels(500,0);

        while(sum < (degrees-10))
        {
            oi_update(sensor);
            sum += sensor->angle;
        }
        oi_setWheels(0,0);



        return 0;
}

double collision_setection(oi_t *sensor, double distance_mm)
{
    double sum = 0;

    while(sum < distance_mm)
    {
        oi_update(sensor);
        sum += sensor->distance;
        oi_setWheels(500,500);
        if(sensor->bumpLeft == 1)
        {
            oi_setWheels(0,0);
            move_back(sensor, 150.0);
            turn_right(sensor, 90);
            move_forward (sensor, 250.0);
            turn_left(sensor, 90);
            sum -= 150.0;
        }
        else if(sensor->bumpRight == 1)
        {
            oi_setWheels(0,0);
            move_back(sensor, 150.0);
            turn_left(sensor, 90);
            move_forward (sensor, 250.0);
            turn_right(sensor, 90);
            sum -= 150.0;
        }



    }
    return 0;
}

// This method Prints To Putty
void putty_print(char arr[], int size)
{



       uart_sendChar(arr[0]);
    uart_sendChar('a');
    uart_sendChar('\r');
}

//Gets scan and passes data to detect_object
//, oi_t *sensor
void putty_scan(int start, int end, cyBOT_Scan_t* getScan)
{

       int data[90];
       int ir, ir_1, ir_2, ir_3;
       char vals[5];
       char angle[5];
       int i = 0;




       while(end >= start)
              {

                  //Get IR data
                  cyBOT_Scan(start, getScan);
                  ir = getScan->IR_raw_val;
                  data[i]  = ir;

                  //increment



                  //Print the IR Values
                  sprintf(vals, "%d",data[i]);
                  sprintf(angle, "%d", start);
                  uart_sendStr("At degree:");
                  uart_sendStr(angle);
                  uart_sendChar('\t');
                  uart_sendStr(vals);
                  uart_sendChar('\n');
                  uart_sendChar('\r');

                  start += 1;
                  i++;
              }



}


//THIS METHOD WILL DETECT THE OBJECT LIKE THE METHOD BELOW
//THEN IT WILL CALL VOID_POINT_PING in order to point scanner towards object get the distance



//void detect_object(float data[], cyBOT_Scan_t* getScan, oi_t *sensor)
//{
// int i = 3;
// int size = 90;
// int is_started = 0;
// int object = 0;
// int start = 0;
// int end = 0;
// int middle = 0;
// float dist = 0;
// int angle = 0;
// int angle_tmp = 0;
// int radial = 0;
// int radial_tmp;
//
// char obj_arr[10];
// char angle_arr[10];
// char dist_arr[16];
// char radial_arr[10];
//
// while(i < size)
// {
//     //(data[i+1] - data[i] < 0)
//     if(((data[i-1] - data[i]) > 10) && !is_started)
//     {
//      is_started = 1;
//      start = i;
//      i++;
//     }
//
//     //(data[i] - data[i+1]) < 0
//     else if(((data[i] - data[i-1]) > 10) && is_started)
//     {
//      is_started = 0;
//      end = i;
//      object+=1;
//      i++;
//
//      middle = (end + start) / 2;
//                dist = data[middle];
//                angle = middle * 2;
//                radial = (end - start)*2;
//
//                if(object == 1) {
//                    radial_tmp = radial;
//                    angle_tmp = angle;
//                }
//
//                else if(radial < radial_tmp) {
//                    radial_tmp = radial;
//                    angle_tmp = angle;
//                }
//
//                      sprintf(obj_arr, "Object: %d", object);
//                      putty_print(obj_arr, 10);
//
//                      sprintf(angle_arr, "Angle: %d", angle);
//                      putty_print(angle_arr, 10);
//
//                      sprintf(dist_arr, "Distance: %.2f", dist);
//                      putty_print(dist_arr, 16);
//
//                      sprintf(radial_arr, "Radial: %d", radial);
//                      putty_print(radial_arr, 10);
//     }
//
//     else
//     {
//         i++;
//     }
// }
//
// cyBOT_Scan(angle_tmp, getScan);
// turn_left(getScan, angle_tmp);
// move_forward (sensor, 30);








