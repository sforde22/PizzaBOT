

/**
 * main.c
 */
#include "open_interface.h"
#include "movement.h"
#include "cyBot_uart.h"
#include "lcd.h"
#include "cyBot_Scan.h"
#include "Timer.h"

typedef struct{
    int objectNum;
    int firstAngle;
    int objectWidth;
    int objectDistance;
}objectData;

int main(void)
{
//    cyBot_uart_init();
//    lcd_init();
//    char string[] = "Got an ";
//    int i;
//    while(1){
//        int in = cyBot_getByte();
//        lcd_putc(in);
//        for(i = 0; i < 7; i++) {
//            cyBot_sendByte(string[i]);
//        }
//        cyBot_sendByte(in);
//    }
//    //calibration
//    timer_init();
//    lcd_init();
//    cyBOT_init_Scan(0b0011);
//    cyBOT_SERVO_cal();


    timer_init();
    lcd_init();
    cyBOT_init_Scan(0b0011);
    cyBot_uart_init();

    right_calibration_value = 253750;
    left_calibration_value = 1246000;

    char m='n';
    cyBOT_Scan_t* scan_data;

    char distanceCM[25];
    int i = 0;
    int j = 0;

    //preliminary scan to see first distance for better data maybe
    scan_data = calloc(1, sizeof(cyBOT_Scan_t));
    cyBOT_Scan(0, scan_data);
    float obj = scan_data->sound_dist;      // dist of last reading
    free(scan_data);

    objectData* theSMALLEST;


    int W = 0;          //width of obj
    int A =0;            // first angle at detection
    int D = 0;          //Distance at first reading
    int num_obj = 0;    // number of obj
    int isObjStarted = 0;
    while(1){
        theSMALLEST = calloc(1, sizeof(objectData));
        theSMALLEST->objectWidth = 1000;
        scan_data = calloc(1, sizeof(cyBOT_Scan_t));
        do {
            m = cyBot_getByte();
        }while(m != 'm');
        sprintf(distanceCM, "==========================\n\r");
             for(i = 0; i < strlen(distanceCM); ++i){
             cyBot_sendByte(distanceCM[i]);
        }
//        sprintf(distanceCM, "Degrees\tPING Distance (cm)\n\r");
//        for(i = 0; i < strlen(distanceCM); ++i){
//            cyBot_sendByte(distanceCM[i]);
//        }
        for(j = 0; j < 180; j+=3) {                     //scan area from 0-180 degrees
            cyBOT_Scan(j, scan_data);                   //scans at j degree
            W+=3;                                       //keeps track of obj width

            if (scan_data->sound_dist + 10 < obj && scan_data->sound_dist < 110 && isObjStarted == 0){      //sees new obj
              W = 0;                                    //resets obj width
              A = j;                                    //sets angle witch obj is detected
              D = scan_data->sound_dist;                //sets distance from object
              num_obj++;                                //add number of obj dtected
              isObjStarted = 1;
            }

            if (scan_data->sound_dist - 10 > obj && isObjStarted == 1){
                if(W > 6){
                    sprintf(distanceCM, "object number: %d\n\r",num_obj);
                    for(i = 0; i < strlen(distanceCM); ++i){
                                   cyBot_sendByte(distanceCM[i]);
                    }

                    sprintf(distanceCM, "Width: %d Angle First Spotted: %d\n\r", W, A);
                    for(i = 0; i < strlen(distanceCM); ++i){
                        cyBot_sendByte(distanceCM[i]);
                    }

                    sprintf(distanceCM, "Distance: %d\n\n\r", D);
                    for(i = 0; i < strlen(distanceCM); ++i){
                        cyBot_sendByte(distanceCM[i]);
                    }
                    //checks if the object is the smallest, if so put into struct
                    if(W < theSMALLEST->objectWidth){
                        theSMALLEST->firstAngle = A;
                        theSMALLEST->objectDistance = D;
                        theSMALLEST->objectNum = num_obj;
                        theSMALLEST->objectWidth = W;

                        sprintf(distanceCM, "WE HAVE A NEW SMALLEST: %d\n\r",theSMALLEST->objectNum);
                        for(i = 0; i < strlen(distanceCM); ++i){
                             cyBot_sendByte(distanceCM[i]);
                        }
                    }
                    num_obj++;
                }
                num_obj--;
                isObjStarted = 0;

            }

            obj = scan_data->sound_dist;
//            sprintf(distanceCM, "%d\t%5.1f\n\r", j, scan_data->sound_dist);
//            for(i = 0; i < strlen(distanceCM); ++i){
//                cyBot_sendByte(distanceCM[i]);
//            }
        }
        num_obj = 0;
        cyBOT_Scan(((theSMALLEST->firstAngle*2)+theSMALLEST->objectWidth)/2.0, scan_data);
        free(scan_data);
        sprintf(distanceCM, "\nThe Smallest was: object number: %d\n\r",theSMALLEST->objectNum);
        for(i = 0; i < strlen(distanceCM); ++i){
                       cyBot_sendByte(distanceCM[i]);
        }

        sprintf(distanceCM, "Width: %d Angle First Spotted: %d\n\r", theSMALLEST->objectWidth, theSMALLEST->firstAngle);
        for(i = 0; i < strlen(distanceCM); ++i){
            cyBot_sendByte(distanceCM[i]);
        }

        sprintf(distanceCM, "Distance: %d\n\n\r", theSMALLEST->objectDistance);
        for(i = 0; i < strlen(distanceCM); ++i){
            cyBot_sendByte(distanceCM[i]);
        }
        free(theSMALLEST);
    }

    return 0;
}
