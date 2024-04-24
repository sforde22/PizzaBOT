/*
 * movement.h
 *
 *  Created on: Jan 30, 2024
 *      Author: joshs1
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <open_interface.h>
#include <lcd.h>

double uTurn(oi_t *sensor);
double move_blockForward(oi_t *sensor_data);
double move_blockLeft(oi_t *sensor_data);
double move_blockRight(oi_t *sensor_data);
double move_intersection(oi_t *sensor_data);



double turn_right(oi_t *sensor, double degrees);
double turn_left(oi_t *sensor, double degrees);


//double move_forward (oi_t *sensor_data, double distance_mm);
//double turn_right(oi_t *sensor, double degrees);
//double turn_left(oi_t *sensor, double degrees)
//double collision_setection(oi_t *sensor, double distance_mm);
//double move_back (oi_t *sensor_data, double distance_mm);


#endif /* MOVEMENT_H_ */
