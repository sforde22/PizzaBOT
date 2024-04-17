/// Simple 'Hello, world' program
/**
 * This program prints "Hello, world" to the LCD screen
 * @author Chad Nelson
 * @date 06/26/2012
 *
 * updated: phjones 9/3/2019
 * Description: Added timer_init call, and including Timer.h
 */

#include "Timer.h"
#include "lcd.h"
#include "open_interface.h"


int main (void) {
    
    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
    oi_init(sensor_data); // do this only once at start of main()


   lcd_init();
   //move_forward(sensor_data, 1000.0);

 //   Now Move Into Square
   move_forward(sensor_data, 500.0);
   turn_right(sensor_data, 90.0);
   move_forward(sensor_data, 500.0);
   turn_right(sensor_data, 90.0);
   move_forward(sensor_data, 500.0);
   turn_right(sensor_data, 90.0);
   move_forward(sensor_data, 500.0);

//     move_forward(sensor_data, 500.0);
//     turn_left(sensor_data, 90.0);
//     move_forward(sensor_data, 500.0);
//     turn_left(sensor_data, 90.0);
//     move_forward(sensor_data, 500.0);
//     turn_left(sensor_data, 90.0);
//     move_forward(sensor_data, 500.0);



 //  collision_setection(sensor_data, 2000.0);



    oi_free(sensor_data); // do this once at end of main()
	return 0;
}





//void putty_scan(int x, double start, double end, cyBOT_Scan_t* getScan)
//{
//
//    float t;
//    int i = 0;
//    float size = (end - start) /2;
//    float data[90];
//    if(x == 109)
//    {
//        while(end >= start)
//        {
//            cyBOT_Scan(start, getScan);
//            t = getScan->sound_dist;
////            sprintf(scan_data, "%.2f", x);
////            sprintf(angle, "%.0f", start);
//           // putty_confirmation(t, start);
//            start += 2;
//            data[i] = t;
//            i++;
//        }
//    }
//}
//
//void detect_object(float data[])
//{
//    int i = 0;
//    int is_started = 0;
//    int angle_start = 0;
//    int size = sizeof(data);
//    int angle_end = size * 2;
//    int object = 0;
//while(i < size)
//{
//    if ((data[i] - data[i+1]) < 0)
//    {
//       is_started = 1;
//       angle_start = (i+1)*2;
//       i++;
//
//
//    }
//
//    else if(is_started && (data[i+1] - data[i] > 0))
//     {
//       is_started = 0;
//       angle_end = i*2;
//       object++;
//       i++;
//
//       char obj_arr[2];
//       sprintf(obj_arr, "Object: %d", object);
//       putty_confimation(obj_arr);
//     }
//}


//void putty_confirmation(char arr[])
//{
//    int size = sizeof(arr);
//
//    int i = 0;
//    for(i = 0; i < size; i++)
//    {
//        cyBot_sendByte(arr[i]);
//    }
////    cyBot_sendByte('\t');
////    for(i = 0; i < 7; i++)
////    {
////        cyBot_sendByte(scan_data[i]);
////    }
////    cyBot_sendByte('\n');
////    cyBot_sendByte('\r');
//}
