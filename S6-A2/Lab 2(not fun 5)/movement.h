/*
 * movement.h
 *
 *  Created on: Jan 30, 2024
 *      Author: sforde22
 */
#include "open_interface.h"

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

double move_forward(oi_t *sensor_data, double distance_mm);

double turn_right(oi_t *sensor, double degrees);

double turn_left(oi_t *sensor, double degrees);

double move_backward(oi_t *sensor_data, double distance_mm);

double moveWithBumps(oi_t *sensor, double distance_mm);

#endif /* MOVEMENT_H_ */
