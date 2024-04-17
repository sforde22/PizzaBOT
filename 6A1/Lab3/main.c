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
#include "cyBot_uart.h"
#include "cyBot_Scan.h"
#include "movement.h"


int main (void) {

    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
    oi_init(sensor_data); // do this only once at start of main()
    cyBot_uart_init();

   lcd_init();
   //move_forward(sensor_data, 1000.0);

    //Now Move Into Square
//   move_forward(sensor_data, 500.0);
//   turn_right(sensor_data, 90.0);
//   move_forward(sensor_data, 500.0);
//   turn_right(sensor_data, 90.0);
//   move_forward(sensor_data, 500.0);
//   turn_right(sensor_data, 90.0);
//   move_forward(sensor_data, 500.0);

//     move_forward(sensor_data, 500.0);
//     turn_left(sensor_data, 90.0);
//     move_forward(sensor_data, 500.0);
//     turn_left(sensor_data, 90.0);
//     move_forward(sensor_data, 500.0);
//     turn_left(sensor_data, 90.0);
//     move_forward(sensor_data, 500.0);





//       putty_confirmation(x);


          cyBOT_Scan_t* scanData;
          cyBOT_init_Scan(0b0011);
          int x = cyBot_getByte();
          putty_scan(x, 0, 180, &scanData);




  oi_free(sensor_data); // do this once at end of main()
    return 0;
}

