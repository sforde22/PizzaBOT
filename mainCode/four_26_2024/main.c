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
#include "servo.h"
#include "adc.h"
#include "ping.h"
//#include "cyBot_Scan.h"

unsigned char horn = 'a';
unsigned char victorySong = 'abcd';

//left_calibration_value = 1298500;
//right_calibration_value = 285250;

//285250 Right
//1298500 Left

int main (void) {
    

    char direction = 'N';

    int uart_triggered = 1;
    int j = 0;
    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
    oi_init(sensor_data); // do this only once at start of main()

 oi_free(sensor_data);
    innit();

    int madeToDelivery = 1;
    char Instructions;


    while(madeToDelivery){
    char objectsDetected[13] = "";

        Instructions = uart_receive(); //Takes in instructions from puTTy

        if(Instructions == 't') //forward
        {
            move_blockForward(sensor_data);
            scan_intersection(objectsDetected);
            uart_sendStr(objectsDetected);
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
        else if(Instructions == 'm')
        {
            scan_intersection(objectsDetected);
            uart_sendStr(objectsDetected);
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


//    https://git.ece.iastate.edu/tdbolton/cpre-288-project-s4-pg4/-/blob/main/ping.c?ref_type=heads




    oi_free(sensor_data); // do this once at end of main()
	return 0;
}

void scan_intersection(char objDirection[])
{

    int i = 0;

    char left = 'L';
    char middle = 'M';
    char right = 'R';

    int rightCount = 0;
    int middleCount = 0;
    int leftCount = 0;


    float adc_distance;
    float ping_distance;

    for(i = 0; i < 180; i++)
    {
        servo_move(i);
        adc_distance = adc_dist();
//        ping_distance = ping_getDistance();

        if(adc_distance < 12.5763) // || ping_distance < 50.0
        {
            if(i < 60 && rightCount < 4)
            {
                strncat(objDirection, &right, 1);
                rightCount++;
            }
            else if(i > 60 && i < 119 && middleCount < 4)
            {
                strncat(objDirection, &middle, 1);
                middleCount++;
            }
            else if(i >= 120 && leftCount < 4)
            {
                strncat(objDirection, &left, 1);
                leftCount++;
            }
        }
    }
}

void innit()
{
    timer_init();
    lcd_init();
    uart_interrupt_init();
    ping_init();
    adc_init();
    servo_init();
    oi_loadSong(1, 1, horn, 150);
    oi_loadSong(2, 4, victorySong, 500);

}

