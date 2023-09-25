#include <at89c5131.h>
#include "lcd.h"

sbit StartStop = P1^0;
code unsigned char display_msg1[]="   STOPWATCH     ";						//Display msg on 1st line of lcd
code unsigned char display_msg2[]="     ";
unsigned int sec = 0, min = 0;
unsigned int total_count = 0, tlo_count = 0;

void main(){
 TMOD = 0x05;  // set timer 0 in counter mode
 TH0 = 0x00;
 TL0 = 0x00;	
 P1 = 0x0f;    // set p1 port in input mode
  lcd_init();
  lcd_cmd(0x80);													//Move cursor to first line
  lcd_write_string(display_msg1);
 	lcd_cmd(0xC0);													//Move cursor to 2nd line of LCD
// 	lcd_write_string(display_msg2);
 while(1){
	  while(StartStop == 1){     // start timer counting 
	  TR0 = 1;
	  total_count = (TH0*256 + TL0);    // TH0 and TL0 combined forms a number... let say th0 has 6
	  sec = total_count/60;
	  min = sec/60;	
	  lcd_write_char((min/10) + 48);       // 48 is ASCII code for zero ...so to convert integer (let say 3) its ASCII code will be 48+3
	  lcd_write_char((min%10) + 48);
		lcd_write_char(':');
		lcd_write_char((sec/10)%6 + 48);     // when seconds reaches 60 sec it should again display 01 ..02 and so on instead of 61..62
		lcd_write_char((sec%10) + 48);
		lcd_cmd(0xC0);	 
	 }
	 while(StartStop == 0){                   // stop counter 
	  TR0 = 0;
	  total_count = (TH0*256 + TL0);
	  sec = total_count/60;
	  min = sec/60;
	  lcd_write_char((min/10) + 48);       // 48 is ASCII code for zero ...so to convert integer (let say 3) its ASCII code will be 48+3
	  lcd_write_char((min%10) + 48);
		lcd_write_char(':');
		lcd_write_char((sec/10) + 48);
		lcd_write_char((sec%10) + 48);
		lcd_cmd(0xC0);
	 }
 }	

}