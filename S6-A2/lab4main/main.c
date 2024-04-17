

/**
 * main.c
 */
#include "open_interface.h"
#include "movement.h"
#include "cyBot_uart.h"
#include "lcd.h"
#include "cyBot_Scan.h"
#include "Timer.h"
#include "button.h"

typedef struct{
    int objectNum;
    int firstAngle;
    int objectWidth;
    int objectDistance;
}objectData;

int main(void)
{
    timer_init();
    lcd_init();
    button_init();
    cyBot_uart_init();
    int button;
    char string[10];
    int i;

    while(1){
        button = button_getButton();
        if(button != 0){
            lcd_printf("%d",button);
            sprintf(string, "Got a %d\n\r", button);
            for(i = 0; i < strlen(string); ++i){
                cyBot_sendByte(string[i]);
            }
        }
    }

    return 0;
}
