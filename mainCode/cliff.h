/**
 * cliff.h
 * @author Samuel Forde
 */
#ifndef CLIFF_H_
#define CLIFF_H_

#include "open_interface.h"

oi_t *oi_data;

typedef enum {
    WHITE,
    BLACK,
    GRAY
} Color;

void cliff_init(void);

void cliff_detect(Color *left, Color *fleft, Color *fright, Color *right);

Color cliff_identify(int cliff_val);

#endif /* CLIFF_H_ */
