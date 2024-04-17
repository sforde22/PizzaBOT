/**
 * lab6-interrupt_template.c
 *
 * Template file for CprE 288 Lab 6
 *
 * @author Diane Rover, 2/15/2020
 *
 */

#include "Timer.h"
#include "lcd.h"
#include "cyBot_Scan.h"  // For scan sensors
#include "uart-interrupt.h"
#include "cyBOT_uart.h"
#include "movement.h"
#include "open_interface.h"

// Uncomment or add any include directives that you want to use
// #include "open_interface.h"
// #include "movement.h"
// #include "button.h"

// Your code can use the global variables defined in uart-interrupt.c
// They are declared with the extern qualifier in uart-interrupt.h, which makes the variables visible to this file.

#define REPLACEME 0
#define M_PI 3.14159265358979323846

//CALIBRATION CODE
    int main(void)
    {
        timer_init();
        lcd_init();
        cyBOT_init_Scan(0b111);
        cyBOT_SERVO_cal();
    }

//int main(void) {
//    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
//    oi_init(sensor_data); // do this only once at start of main()
//    timer_init(); // Must be called before lcd_init(), which uses timer functions
//    lcd_init();
//
//    uart_interrupt_init();
//    cyBOT_Scan_t scanData;
//    cyBOT_init_Scan(0b0111);
//
//
//timer_waitMillis(200);
//
////move_forward(sensor_data, 100);
////oi_free(sensor_data);
////collision_setection(sensor_data, 1000.0);
////oi_free(sensor_data);
//    while(1)
//    {
//
//    int i = 0;
//    int ir1, ir2, ir3, ir_avg;
//    int object_start = 0;
//    int obj_wid;
//    int obj_count = 0;
//
//    float small_width = 0;
//    int small_angle = 0;
//    float small_dist = 0;
//
//    int angular_wid;
//    int start_angle;
//    int end_angle;
//    int middle_angle;
//    int middle_snap;
//    double fin_angle;
//
//    char obj_arr[10];
//    char width_arr[10];
//    char angle_arr[10];
//    char dist_arr[10];
//    char ir_arr[10];
//
//    float dist;
//    float FIN_WIDTH = 0;
//
//
//    right_calibration_value = 295750;
//    left_calibration_value = 1314250;
//        //NEED TO PUT A FLAG HERE I THINK
//
//
//    for(i = 0; i < 180; i+=2)
//        {
//                cyBOT_Scan(i, &scanData);
//                ir1 = scanData.IR_raw_val;
//                ir2 = scanData.IR_raw_val;
//                ir3 = scanData.IR_raw_val;
//                ir_avg = (ir1 + ir2 + ir3) / 3;
//                sprintf(ir_arr, "%d", ir_avg);
//                uart_sendStr(ir_arr);
//                uart_sendChar('\n');
//                uart_sendChar('\r');
//
//                if(ir_avg > 1000)
//                {
//                    if(object_start == 0)
//                    {
//                        object_start = 1;
//                        start_angle = i;
//                        obj_wid = 1;
//                        obj_count += 1;
//
//
//                    }
//                    else
//                    {
//                        obj_wid += 1;
//
//                    }
//                }
//                else if(object_start == 1)
//                {
//                    if(obj_wid > 10)
//                    {
//                        end_angle = i;
//                        angular_wid = end_angle - start_angle / 2;
//                        middle_angle = end_angle + start_angle / 2;
//
//                        dist = scanData.sound_dist;
//
//                        FIN_WIDTH = 2*3.14159265358979323846  * dist * (end_angle - start_angle)/360;
//
//                        if((FIN_WIDTH < small_width) || obj_count == 1)
//                        {
//                            small_width = FIN_WIDTH;
//                            small_angle = middle_angle;
//                            small_dist = dist;
//                            middle_snap = middle_angle;
//                        }
//
//                        //PRINT TO PUTTY HERE
//
//                        sprintf(obj_arr, "Object: %d", obj_count);
//                        sprintf(width_arr, "Linear: %f", FIN_WIDTH);
//                        sprintf(angle_arr, "%d", middle_angle);
//                        sprintf(dist_arr, "%f", dist);
//                        uart_sendStr(obj_arr);
//                        uart_sendChar('\n');
//                        uart_sendChar('\r');
//                        uart_sendStr(width_arr);
//                        uart_sendChar('\n');
//                        uart_sendChar('\r');
//                        uart_sendStr(angle_arr);
//                        uart_sendChar('\n');
//                        uart_sendChar('\r');
//                        uart_sendStr(dist_arr);
//                        uart_sendChar('\n');
//                        uart_sendChar('\r');
//
//                        object_start = 0;
//                        start_angle = 0;
//                        end_angle = 0;
//                        obj_wid = 0;
//
//
//
//
//                    }
//                    else
//                    {
//                        object_start = 0;
//                        start_angle = 0;
//                        end_angle = 0;
//                        obj_wid = 0;
//                        obj_count -= 1;
//
//
//                    }
//
//
//                }
//
//
//
//
//        }
//
//    cyBOT_Scan(middle_snap, &scanData);
//
//    if(small_angle <= 90)
//    {
//      //MOVE TO THE RIGHT
//                        //PUT BUMP DETECTION HERE
//                        fin_angle = 90.0 - small_angle;
//                        turn_right(sensor_data, fin_angle);
//                        collision_setection(sensor_data, small_dist*10);
//
//
//                    }
//                    else if(small_angle > 90)
//                    {
//                        // MOVE TO THE LEFT
//                        //PUT BUMP DETECTION HERE
//                        fin_angle = 180 - small_angle;
//                        turn_left(sensor_data, fin_angle - 10);
//                        collision_setection(sensor_data, small_dist*10);
//
//
//                    }
//
//
//
//
//
//    oi_free(sensor_data);
//    break;
//
//    }
//
//
//    }
