/**
 * cliff.c
 * @author Samuel Forde
 */
#include "cliff.h"

#include "open_interface.h"

oi_t *oi_data;

void cliff_init(void) {
    oi_t *oi_data = oi_alloc();
    oi_init(oi_data);
}

void cliff_detect(Color* left, Color* fleft, Color* fright, Color* right) {
    oi_update(oi_data);
    int cliff1, cliff2, cliff3, cliff4;
    cliff1 = oi_data->cliffLeftSignal;
    cliff2 = oi_data->cliffFrontLeftSignal;
    cliff3 = oi_data->cliffFrontRightSignal;
    cliff4 = oi_data->cliffRightSignal;
    *left = cliff_identify(cliff1);
    *fleft = cliff_identify(cliff2);
    *fright = cliff_identify(cliff3);
    *right = cliff_identify(cliff4);
}

Color cliff_identify(int cliff_val) {
    Color toReturn;
    if(cliff_val < 1000){
        toReturn = BLACK;
    } else if(cliff_val < 2000) {
        toReturn = GRAY;
    } else {
        toReturn = WHITE;
    }
    return toReturn;
}

const char* getCliffState(Color cliffSensor) {
    switch(cliffSensor){
        case BLACK: return "Black";
        case WHITE: return "White";
        case RED: return "Red";
    }
    return 0;
}
