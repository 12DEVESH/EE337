#include <at89c5131.h>
#include <string.h>
#include "lcd.h"

sbit start_stop_pin = P1^0;
sbit event_counter_pin = P3^4;

unsigned char sec=0, min=0;
unsigned int count=0;
bit flag=0;

unsigned int Value()  // reads the timer0 once and will get count subtracting the new value of timer0
{
    unsigned int count;
	
    count = Timer_Count;   // Calculate the elapsed time
    return count;
}
void main()
{
    lcd_init(); // Initialize the LCD module
    TMOD = 0x05; // Set Timer 0 in mode 1
    TH0 = 0x00; // Set initial value of Timer 0 to 0
    TL0 = 0x00;
    TR0 = 0; // Stop Timer 0 initially
    ET0 = 1; // Enable Timer 0 interrupt
    EA = 1; // Enable global interrupt
    lcd_cmd(0x80); // Move cursor to first line, first position
    lcd_write_string("STOPWATCH"); // Display "STOPWATCH" on the LCD
    while(1)
    {
        if(start_stop_pin == 1) // Check if the start/stop switch is ON
        {
            flag=1; // Set the flag to indicate measurement has started
            TR0 = 1; // Start Timer 0
            while(start_stop_pin == 1); // Wait for the switch to turn OFF
            TR0 = 0; // Stop Timer 0
            flag=0; // Reset the flag to indicate measurement has stopped
					  
            sec = count/60; // Calculate the number of seconds
            min = sec/60; // Calculate the number of minutes
            sec %= 60; // Calculate the remaining seconds
            lcd_cmd(0xC0); // Move cursor to second line, first position
            lcd_write_string("Time: "); // Display "Elapsed Time:" on the LCD
					  msdelay(500);
					  
					  lcd_write_char((min/10)+48); // Display tens digit of minutes
            lcd_write_char((min%10)+48); // Display ones digit of minutes
            lcd_write_char(':'); // Display ":" separator
            lcd_write_char((sec/10)+48); // Display tens digit of seconds
            lcd_write_char((sec%10)+48); // Display ones digit of seconds
            count = 0; // Reset the event counter
					  msdelay(500);
        }
        else
        {
            if(flag==0)
            {   
                lcd_cmd(0xC0); // Move cursor to second line, first position
                lcd_write_string("Press START"); // Display "Press START" on the LCD
            }
        }
    }
}
