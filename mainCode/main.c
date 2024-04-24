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
#include "uart-interrupt.h"
#include "movement.h"
#include "cyBot_Scan.h"

unsigned char horn = 'a';
unsigned char victorySong = 'abcd';

struct Obstacle {
       double edge_max;
       double distance;
       double width;
       double direction;
       double diameter;
   };


int main (void) {
    
    char direction = 'N';

    int uart_triggered = 1;
    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
    oi_init(sensor_data); // do this only once at start of main()
    innit();

    int madeToDelivery = 1;
    char Instructions;


    while(madeToDelivery){

        Instructions = uart_receive(); //Takes in instructions from puTTy

        if(Instructions == 't') //forward
        {
            move_blockForward(sensor_data);
        }
        else if(Instructions == 'f') // left
        {
            move_intersection(sensor_data);
            turn_left(sensor_data, 90.0);
            move_blockForward(sensor_data);
            switch(direction){
                case 'N':
                    direction = 'W';
                    break;
                case 'S':
                    direction = 'E';
                    break;
                case 'W':
                    direction = 'S';
                    break;
                case 'E':
                    direction = 'N';
                    break;
            }
            ping_getDistance();
        }
        else if(Instructions == 'h') //right
        {
            move_intersection(sensor_data);
            turn_left(sensor_data, 90.0);
            move_blockForward(sensor_data);
            switch(direction){
                case 'N':
                    direction = 'E';
                    break;
                case 'S':
                    direction = 'W';
                    break;
                case 'W':
                    direction = 'N';
                    break;
                case 'E':
                    direction = 'S';
                    break;
            }
        }
        else if(Instructions == 'g') // U - Turn
        {
            turn_left(sensor_data, 180);
            move_blockForward(sensor_data);
            switch(direction){
                case 'N':
                    direction = 'S';
                    break;
                case 'S':
                    direction = 'N';
                    break;
                case 'W':
                    direction = 'E';
                    break;
                case 'E':
                    direction = 'W';
                    break;
            }
        }
        else if(Instructions == 'p') // Horn
        {
            oi_play_song(1);
        }
        else if(Instructions == 's') // Victory Song
        {
            oi_play_song(2);
        }
        else if(Instructions == 'z') // Go Up Driveway
        {

        }



        else if(Instructions == 'q') // Made to Delivery
        {
            break;
        }
    }






    oi_free(sensor_data); // do this once at end of main()
	return 0;
}


void innit()
{
    ping_init();
    oi_loadSong(1, 1, horn, 150);
    oi_loadSong(2, 4, victorySong, 500);
    uart_interrupt_init(); //Initialize the Interrupt
    lcd_init(); //Initialize the lcd
    cyBOT_Scan_t* scanData; //Declare the scanData
    cyBOT_init_Scan(0b0111); //Initailize the ....
}

