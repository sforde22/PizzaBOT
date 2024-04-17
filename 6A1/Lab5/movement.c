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
}

// This method Prints To Putty
void putty_confirmation(char arr[], int size)
{
//    int size = sizeof(arr) / sizeof(arr[0]);
//    sprintf(scan_data, "%.2f", x);
//    sprintf(angle, "%.0f", start);
    int i = 0;
    for(i = 0; i < size; i++)
    {
        cyBot_sendByte(arr[i]);
    }
    cyBot_sendByte('\n');
    cyBot_sendByte('\r');
}

//Gets scan and passes data to detect_object
void putty_scan(int x, double start, double end, cyBOT_Scan_t* getScan, oi_t *sensor)
{

    float t;
    char vals[5];
    int i = 0;
   // float size = 90;
    float data[90];
    if(x == 109)
    {
        while(end >= start)
        {
            cyBOT_Scan(start, getScan);
            t = getScan->sound_dist;
            data[i]  = t;
            start += 2;
            i++;



        }

//        sprintf(vals, "%.2f",data);
//        putty_confirmation(vals, 5);


        detect_object(data, getScan, sensor);
    }
}

//oi_t *sensor,
//void detect_object(float data[]  /*cyBOT_Scan_t* getScan*/)
//{
// int i = 3;
// int size = 90;
// int is_started = 0;
// int object = 0;
// int start = 0;
// int end = size*2;
// int middle = 0;
// //int middle_tmp = 0;
// float dist = 0;
//// float dist_tmp = 0;
// int angle = 0;
//// int angle_tmp = 0;
// int radial = 0;
//// float linear = 0;
// //float linear_tmp = 0;
//// int turn = 0;
//
// char obj_arr[10];
// char angle_arr[10];
// //char angle_arr_tmp[10];
// char dist_arr[16];
// char radial_arr[10];
// //char linear_arr[12];
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
//      end = i-1;
//      object++;
//
//
//      middle = (end + start) / 2;
//      dist = data[middle];
//      angle = middle * 2;
//      radial = (end - start)*2;
//
//      i++;
////      linear = 2 * PI * dist * (angle / 360.0);
//
////      if(linear == 0 && linear_tmp == 0)
////       {
////          middle_tmp = middle;
////          dist_tmp = dist;
////          angle_tmp = angle;
////          linear_tmp = linear;
////       }
////      if(linear < linear_tmp)
////      {
////          middle_tmp = middle;
////          dist_tmp = dist;
////          angle_tmp = angle;
////          linear_tmp = linear;
////      }
//
//
//
//      sprintf(obj_arr, "Object: %d", object);
//      putty_confirmation(obj_arr, 10);
//
//      sprintf(angle_arr, "Angle: %d", angle);
//      putty_confirmation(angle_arr, 10);
//
//      sprintf(dist_arr, "Distance: %.2f", dist);
//      putty_confirmation(dist_arr, 16);
//
//      sprintf(radial_arr, "Radial: %d", radial);
//      putty_confirmation(radial_arr, 10);
//
////      sprintf(linear_arr, "Linear: %.2f", linear);
////      putty_confirmation(linear_arr, 10);
//     }
//
//     else
//     {
//         i++;
//     }
// }
//
//
//
//// cyBOT_Scan(angle_tmp, getScan);
//
//}







void detect_object(float data[], cyBOT_Scan_t* getScan, oi_t *sensor)
{
 int i = 3;
 int size = 90;
 int is_started = 0;
 int object = 0;
 int start = 0;
 int end = 0;
 int middle = 0;
 float dist = 0;
 int angle = 0;
 int angle_tmp = 0;
 int radial = 0;
 int radial_tmp;

 char obj_arr[10];
 char angle_arr[10];
 char dist_arr[16];
 char radial_arr[10];

 while(i < size)
 {
     //(data[i+1] - data[i] < 0)
     if(((data[i-1] - data[i]) > 10) && !is_started)
     {
      is_started = 1;
      start = i;
      i++;
     }

     //(data[i] - data[i+1]) < 0
     else if(((data[i] - data[i-1]) > 10) && is_started)
     {
      is_started = 0;
      end = i;
      object+=1;
      i++;

      middle = (end + start) / 2;
                dist = data[middle];
                angle = middle * 2;
                radial = (end - start)*2;

                if(object == 1) {
                    radial_tmp = radial;
                    angle_tmp = angle;
                }

                else if(radial < radial_tmp) {
                    radial_tmp = radial;
                    angle_tmp = angle;
                }

                      sprintf(obj_arr, "Object: %d", object);
                      putty_confirmation(obj_arr, 10);

                      sprintf(angle_arr, "Angle: %d", angle);
                      putty_confirmation(angle_arr, 10);

                      sprintf(dist_arr, "Distance: %.2f", dist);
                      putty_confirmation(dist_arr, 16);

                      sprintf(radial_arr, "Radial: %d", radial);
                      putty_confirmation(radial_arr, 10);
     }

     else
     {
         i++;
     }
 }

 cyBOT_Scan(angle_tmp, getScan);
// turn_left(getScan, angle_tmp);
// move_forward (sensor, 30);


}





