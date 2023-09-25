#include <at89c5131.h>
#include <string.h>
#include "lcd.h"

/* https://www.cs.uic.edu/~jbell/CourseNotes/C_Programming/CharacterStrings.html#:~:text=Overview,terminated%20by%20a%20null%20byte.
   to know more about strings i reffered this site */

code unsigned char display_msg1[]=" ENTER PASSWORD:     ";						//Display msg on 1st line of lcd
code unsigned char display_msg2[]="CORRECT PASSWORD   ";//Display msg on 1st line of lcd
code unsigned char display_msg3[]=" ACCESS GRANTED  ";
code unsigned char display_msg4[]=" WRONG PASSWORD  "	;
code unsigned char display_msg5[]=" ACCESS DENIED   ";
code unsigned char correct_pass[]= "15A8*D6#"; // the terminating null byte is stored automatically 
unsigned int i,Value;
unsigned char a[9];
sbit R0=P3^4;	//row0
sbit R1=P3^5;	//row1
sbit R2=P3^6;	//row2
sbit R3=P3^7; //row3

void polling(void)                            //keep checking for keyboard input after first key is relaeased
{
  while(P3 == 0x0f){ 
			P3 = P3 & 0x0F;}  // check if any key pressed
/*now find row*/	
	    msdelay(20);        //debounce time 
			P3 = P3 & 0x0F;
  }	

void main(){
  lcd_init();
	lcd_cmd(0x80);													//Move cursor to first line
	msdelay(4);
	lcd_write_string(display_msg1);
	msdelay(4);
	
/*******************************KEYBOARD INPUT CODE********************************************/	 
/* to print the pressed letter bring cursor to 2nd row and keep updating address*/			
      lcd_cmd(0xc0);													//Move cursor to 2nd line of LCD
 	    msdelay(4);  
    
  for(i=0;i<8;i++){
		  P3 = 0x0f; //make p3 as input port 
		  while( P3 != 0x0f ){
			  P3 = P3 & 0x0F;}  //ground p3.7 to p3.4 (rows) and check for inputs(columns)
      while( P3 == 0x0f){ 
			  P3 = P3 & 0x0F;}  // check if any key pressed
/*now ensure key pressed*/	
	    msdelay(20);        //debounce time 
			P3 = P3 & 0x0F;
			while( P3 == 0x0F){
			  polling();}			
    
/*now find row*/			
      R0 = 0;   // check for row 0
			R1 = 1;
      R2 = 1;
			R3 = 1;	
      if(P3 == 0xEE) // row0 column3 A
			{ lcd_write_char('A');
			   a[i] = 'A';
			   }
      else if(P3 == 0xED) // row0 column2 3
			{ lcd_write_char('3');
			   a[i] = '3';
			   }
      else if(P3 == 0xEB) // row0 column1 2
			{ lcd_write_char('2');
			   a[i] = '2';
			  }
      else if(P3 == 0xE7) // row0 column0 1
			{ lcd_write_char('1');
			   a[i] = '1';
			   }	
		
      R0 = 1;   // check for row 1
			R1 = 0;
      R2 = 1;
			R3 = 1;	
      if(P3 == 0xDE) // row1 column3 B
			{ lcd_write_char('B');
			   a[i] = 'B';
         	}
      else if(P3 == 0xDD) // row1 column2 6
			{ lcd_write_char('6');
			   a[i] = '6';
			   }
      else if(P3 == 0xDB) // row1 column1 5
			{ lcd_write_char('5');
			   a[i] = '5';
			   }
      else if(P3 == 0xD7) // row1 column0 4
			{ lcd_write_char('4');
			   a[i] = '4';
			   }				
			
      R0 = 1;   // check for row 2
			R1 = 1;
      R2 = 0;
			R3 = 1;	
      if(P3 == 0xBE) // row2 column3 C
			{ lcd_write_char('C');
			   a[i] = 'C';
			   }
      else if(P3 == 0xBD) // row2 column2 9
			{ lcd_write_char('9');
			   a[i] = '9';
			   }
      else if(P3 == 0xBB) // row2 column1 8
			{ lcd_write_char('8');
			   a[i] = '8';
			   }
      else if(P3 == 0xB7) // row2 column0 7
			{ lcd_write_char('7');
			   a[i] = '7';
			   }

      R0 = 1;   // check for row 3
			R1 = 1;
      R2 = 1;
			R3 = 0;	
      if(P3 == 0x7E) // row3 column3 D
			{ lcd_write_char('D');
			   a[i] = 'D';
			  }
      else if(P3 == 0x7D) // row3 column2 #
			{ lcd_write_char('#');
			   a[i] = '#';
			   }
      else if(P3 == 0x7B) // row3 column1 0
			{ lcd_write_char('0');
			   a[i] = '0';
			   }
      else if(P3 == 0x77) // row3 column0 *
			{ lcd_write_char('*');
			   a[i] = '*';
			   }
			
	}		
/*******************************COMPARE STRINGS STORED*****************************************/
  a[8] = '\0'; 
	Value  = strcmp(correct_pass,a);
  if(Value == 0){ 
		  	lcd_cmd(0x01);	// LCD clear
	      msdelay(4);
	      lcd_cmd(0x80);
		    msdelay(4);
	      lcd_write_string(display_msg2);    
        lcd_cmd(0xc0);													//Move cursor to 2nd line of LCD
 	      msdelay(4);
        lcd_write_string(display_msg3);	}		
	else{
		  	lcd_cmd(0x01);	// LCD clear
	      msdelay(4);
	      lcd_cmd(0x80);
		    msdelay(4);
	      lcd_write_string(display_msg4);    
        lcd_cmd(0xc0);													//Move cursor to 2nd line of LCD
 	      msdelay(4);
        lcd_write_string(display_msg5);	      }
  while(1);
}
	