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

int main(void) {
    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
    oi_init(sensor_data); // do this only once at start of main()
    timer_init(); // Must be called before lcd_init(), which uses timer functions
    lcd_init();

    uart_interrupt_init();
    cyBOT_Scan_t* scanData;
    cyBOT_init_Scan(0b0111);

    timer_waitMillis(200);

    adc_init();

    int j = 1;
    int i = 0;
    char adc_string[15]; // Assuming ADC values won't exceed 5 characters (including null terminator)
    char adc_string2[15];
    double distance =  0.0;


    while (j == 1) {
            // Read from the ADC
            uint16_t adc_value1 = adc_read();
            timer_waitMillis(100);
            uint16_t adc_value2 = adc_read();
            timer_waitMillis(100);
            uint16_t adc_value3 = adc_read();
            timer_waitMillis(100);
            uint16_t adc_value4 = adc_read();

            uint16_t result = (adc_value1+adc_value2+adc_value3+adc_value4) / 4;
            sprintf(adc_string, "%u", result);
            lcd_puts("Raw: ");
            lcd_puts(adc_string);
            lcd_puts(" New: ");

            //Convert Here
            distance = -8.037e-9 * pow(result, 3) + 6.388e-5 * pow(result, 2) - 0.1719 * result + 169.1;
//            distance /=2;

            sprintf(adc_string2, "%f.2", distance);

            lcd_puts(adc_string2);

            uart_sendStr(adc_string);
            uart_sendChar('\n');
            uart_sendChar('\r');


            timer_waitMillis(1000);
            lcd_clear();
            i++;



            // Convert the ADC value to meaningful data (e.g., IR intensity or distance)
            // For example, you might have a function like ir_data = convert_to_ir_data(adc_value);

            // Display or process the converted data
            // For example, you might have a function like display(ir_data);

            // Add a delay to control the sampling rate
            // Adjust the delay as necessary based on your application requirements
            // For example, delay_ms(100); // Delay for 100 milliseconds
        }


}


