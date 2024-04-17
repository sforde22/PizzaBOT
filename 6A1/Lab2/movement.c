/*
 * movement.c
 *
 *  Created on: Jan 30, 2024
 *      Author: joshs1
 */

//#include "open_interface.c"
#include "open_interface.h"
#include <string.h>

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

        while(sum < 80)
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




