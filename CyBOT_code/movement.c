/*
 * movement.c
 *
 *  Created on: Jan 30, 2024
 *      Author: sforde22
 */
#include "open_interface.h"
#include "lcd.h"

double move_forward(oi_t *sensor_data, double distance_mm) {
    double sum = 0;
    oi_setWheels(500,500);
        while (sum < distance_mm) {
            oi_update(sensor_data);
            sum += sensor_data -> distance;
        }
    oi_setWheels(0,0);
    return 0;
}

double move_backward(oi_t *sensor_data, double distance_mm) {
    double sum = 0;
    oi_setWheels(-500,-500);
        while (sum > (distance_mm*-1)) {
            oi_update(sensor_data);
            sum += sensor_data -> distance;
        }
    oi_setWheels(0,0);
    return 0;
}

double turn_right(oi_t *sensor, double degrees){
    double sum = 0;
    sensor->angle = 0;
    oi_setWheels(-100,100);
        while (sum > (degrees*-1)){
            oi_update(sensor);
            sum += sensor->angle;

        }
   oi_setWheels(0,0);
   return 0;
}

double turn_left(oi_t *sensor, double degrees){
    double sum = 0;
        oi_setWheels(100,-100);
            while (sum < degrees){
                oi_update(sensor);
                sum += sensor->angle;
            }
       oi_setWheels(0,0);
       return 0;

}

double moveWithBumps(oi_t *sensor, double distance_mm){
    double sum = 0;
    oi_setWheels(500, 500);
    while(sum < distance_mm){
        oi_update(sensor);
        sum += sensor->distance;
        if(sensor->bumpLeft){
            move_backward(sensor, 150);
            turn_right(sensor, 90);
            moveWithBumps(sensor, 50);
            turn_left(sensor, 90);
            sum -= 150;
            oi_setWheels(500, 500);
        }
        if(sensor->bumpRight){
            move_backward(sensor, 150);
            turn_left(sensor, 90);
            moveWithBumps(sensor, 50);
            turn_right(sensor, 90);
            sum -= 150;
            oi_setWheels(500, 500);
        }
    }
    oi_setWheels(0,0);
    return 0;
}
