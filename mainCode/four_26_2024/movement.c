/*
 * movement.c
 *
 *  Created on: Jan 30, 2024
 *      Author: joshs1
 */

//#include "open_interface.c"
#include "open_interface.h"
#include <string.h>
#include "uart-interrupt.h"
#include "cyBot_Scan.h"
#include "cliff.h"

double block_length = 590.0;

Color* left;
Color* fleft;
Color* right;
Color* fright;
Color* cliffSensor;
const char* cliffState;


void cliff_print(){

    cliff_detect(left, fleft,fright,right);
        if(left == WHITE || left == BLACK) {
            cliffSensor = left;
            char color[15];
            sprintf(color, "Left: %s ", getCliffState(cliffSensor));
            uart_sendStr(color);
            free(cliffSensor);
                   }


            if(fleft == WHITE || fleft == BLACK) {
                        cliffSensor = fleft;
                        char color[15];
                        sprintf(color, "fLeft: %s ", getCliffState(cliffSensor));
                        uart_sendStr(color);
                        free(cliffSensor);
                    }

        if(fright == WHITE || fright == BLACK) {
            cliffSensor = fright;
            char color[15];
            sprintf(color, "fright: %s ", getCliffState(cliffSensor));
            uart_sendStr(color);
            free(cliffSensor);
        }
        if(right == WHITE || right == BLACK) {
            cliffSensor = right;
            char color[15];
            sprintf(color, "right: %s ", getCliffState(cliffSensor));
            uart_sendStr(color);
            free(cliffSensor);
        }


}

//Moves 1 block forward
//called when the interrupt is triggered
double move_blockForward(oi_t *sensor_data)
{
    cliff_print();
    double block = 0; // distance member in oi_t struct is type double
    oi_setWheels(100,100); //move forward at full speed

           while (block < block_length) {


               oi_update(sensor_data);
               block += sensor_data -> distance; // use -> notation since pointer

               char buf[128];
               sprintf(buf, "%f", block);

               lcd_printf("Speed: 25 MPH");


           }

     oi_setWheels(0,0);
     return 0;
}

double move_intersection(oi_t *sensor_data){

    double block = 0; // distance member in oi_t struct is type double
        oi_setWheels(50,50); //move forward at full speed

               while (block < 150) {
                   oi_update(sensor_data);
                   block += sensor_data -> distance; // use -> notation since pointer

                   char buf[128];
                   sprintf(buf, "%f", block);

                   lcd_printf("Speed: 25 MPH");


               }

         oi_setWheels(0,0);
         return 0;

}


double move_uTurn(oi_t *sensor_data)
{
    double block = 0; // distance member in oi_t struct is type double
    oi_setWheels(200,200); //move forward at full speed

           while (block < block_length) {
               oi_update(sensor_data);
               block += sensor_data -> distance; // use -> notation since pointer

               char buf[128];
               sprintf(buf, "%f", block);

               lcd_printf(buf);


           }
     return 0;
}


double turn_right(oi_t *sensor, double degrees)
{
    double sum = 90;
    oi_setWheels(-5,40);

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
        oi_setWheels(40,-5);

        while(sum < degrees)
        {
            oi_update(sensor);
            sum += sensor->angle;
        }
        oi_setWheels(0,0);



        return 0;
}































//This is the function for turning when cyBot
//is in the middle of the intersection


//This is the function for turning when cyBot
//is in the middle of the intersection

double uturn(oi_t *sensor, double degrees)
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



//double collision_setection(oi_t *sensor, double distance_mm)
//{
//    double sum = 0;
//
//    while(sum < distance_mm)
//    {
//        oi_update(sensor);
//        sum += sensor->distance;
//        oi_setWheels(500,500);
//        if(sensor->bumpLeft == 1)
//        {
//            oi_setWheels(0,0);
//            move_back(sensor, 150.0);
//            turn_right(sensor, 90);
//            move_forward (sensor, 250.0);
//            turn_left(sensor, 90);
//            sum -= 150.0;
//        }
//        else if(sensor->bumpRight == 1)
//        {
//            oi_setWheels(0,0);
//            move_back(sensor, 150.0);
//            turn_left(sensor, 90);
//            move_forward (sensor, 250.0);
//            turn_right(sensor, 90);
//            sum -= 150.0;
//        }
//
//
//
//    }
//}


