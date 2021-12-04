/*
 * LCD.c
 *
 * Created: 21/10/2019 12:57:10 م
 * Author : mohamed khaled
 */ 
#include <avr/io.h>
#include <util/delay.h> 
#include "lcd.h"  






void LCD_SEND_A_COMMAND (unsigned char command){  
	
 #ifdef EIGHT_BIT_MODE 
 LCD_CHECK_LCD_ISBUSY();
 LCD_control &= ~(1<<RS_switch);
 LCD_control &= ~(1<<ReadWrite);

 LCD_port = command ;
 LCD_KICK(); 
 
 #endif 
 
 
 #ifdef FOUR_BIT_MODE
  //LCD_CHECK_LCD_ISBUSY(); 
  LCD_control &= ~(1<<RS_switch);
  LCD_port = (LCD_port & 0x0F) | (command & 0xF0); 
  
  LCD_control &= ~(1<<ReadWrite);
  LCD_KICK();  
 
  LCD_port = (LCD_port & 0x0F) | (command <<4); 
  LCD_control &= ~(1<<RS_switch);
  LCD_control &= ~(1<<ReadWrite);
  LCD_KICK();  
  //LCD_port = 0; 
   
 #endif
	
}





void LCD_KICK(void){
LCD_control &= ~(1<<EN_switch); 
  _delay_us(200);
  LCD_control |= (1<<EN_switch) ; 
  _delay_ms(50);
}

 
 void LCD_CLEAR(void){
	 
	 LCD_SEND_A_COMMAND(LCD_CLEAR_SCREEN); 
	 _delay_ms(10); 
 }



void LCD_INIT(void){ 
	
	_delay_ms(20);  
	DataDir_LCD_control |= (1<<EN_switch | 1<<ReadWrite | 1<<RS_switch) ;
	DataDir_LCD_port = 0xff; 
	LCD_control &= ~(1<<EN_switch | 1<<ReadWrite | 1<<RS_switch) ; 
	_delay_ms(15);
	 LCD_CLEAR(); 
	#ifdef EIGHT_BIT_MODE
	LCD_SEND_A_COMMAND(LCD_FUNCTION_8BIT_2LINES); 
    #endif

   #ifdef FOUR_BIT_MODE   
   LCD_SEND_A_COMMAND(0x02); 
   LCD_SEND_A_COMMAND(LCD_FUNCTION_4BIT_2LINES);
   #endif
	
	LCD_SEND_A_COMMAND(LCD_ENTRY_MODE); 
	LCD_SEND_A_COMMAND(LCD_BEGIN_AT_FIRST_RAW); 
    LCD_SEND_A_COMMAND(LCD_DISP_ON  ); 
} 



void LCD_SEND_A_CHAR ( unsigned char character){
	
	#ifdef EIGHT_BIT_MODE 
	LCD_CHECK_LCD_ISBUSY(); 
	LCD_control |= (1<<RS_switch); 
	LCD_control &= ~(1<<ReadWrite); 
	LCD_port = character; 
	LCD_KICK(); 
    #endif 
	
	
	
	#ifdef FOUR_BIT_MODE
	LCD_port = (LCD_port & 0x0f) | (character & 0xf0); 
	LCD_control |= (1<<RS_switch);
	LCD_control &= ~(1<<ReadWrite);
	LCD_KICK(); 
	LCD_port = (LCD_port & 0x0f) | ( character << 4 );  
	LCD_control |= (1<<RS_switch);
	LCD_control &= ~(1<<ReadWrite);
	LCD_KICK();
	#endif
}  



void LCD_CHECK_LCD_ISBUSY(){
	DataDir_LCD_port &= ~(0xff<<DATA_shift);  
	LCD_control &= ~(1<<RS_switch); 
	LCD_control |= (1<<ReadWrite);  
	LCD_KICK(); 
	DataDir_LCD_port = 0xff; 
	LCD_control &= ~(1<<ReadWrite); 
} 


void LCD_GOTO_XY( unsigned char line , unsigned char position ) {
	if ( line == 0 )
	{  
		if(position >= 0 && position < 16) 
			LCD_SEND_A_COMMAND( 0x80 | position );  
		 
	}
	else if ( line == 1)
	{ 
		if(position >= 0 && position < 16)
		LCD_SEND_A_COMMAND( 0xC0 | position ); 
	}
	
	
	}
	
	


	
 



void LCD_SEND_A_STRING( char* string) {
	
	int i=0 ;  
	int count = 0 ; 
	while (string[i] > 0 )
	{ 
		count++;
		LCD_SEND_A_CHAR(string[i]);  
		i++;    
		
		if (count == 16 )
		{  
			LCD_GOTO_XY(1,0);
			
		} 
		else if (count==32 || count == 33)
		{  
			LCD_CLEAR();  
			LCD_GOTO_XY(0,0); 
			count = 0;
              
		} 
		
	}
	
	
	
} 


/*
void LCD_SEND_INT (int number){  
	
	int rem =0 ; 
	if(number> 99999){ 
		rem = number % 100000 ; 
		number = number /100000; 
      	LCD_SEND_A_CHAR((char)(number+48));   
		number = rem ;
	} 
	if(number> 9999){ 
		rem = number % 10000 ; 
		number = number /10000; 
      	LCD_SEND_A_CHAR((char)(number+48));   
		number = rem ;
	}
	if(number> 999){ 
		rem = number % 1000 ; 
		number = number /1000; 
      	LCD_SEND_A_CHAR((char)(number+48));   
		number = rem ;
	}
	if(number> 99){ 
		rem = number % 100 ; 
		number = number /100; 
      	LCD_SEND_A_CHAR((char)(number+48));   
		number = rem ;
	}
	 
	if(number> 9){ 
		rem = number % 10 ; 
		number = number /10; 
      	LCD_SEND_A_CHAR((char)(number+48));  
		number = rem ; 
	}   
	 
	LCD_SEND_A_CHAR((char)(number+48));
	
  
}
*/	  
void LCD_SEND_INT (int number){
	
	char str[7]; 
	sprintf(str, "%2d" ,number); 
	LCD_SEND_A_STRING(str); 

} 


void LCD_SEND_REALNUM (double RealNum ){
	
	char str[16]; 
	char tmpsign = (RealNum<0) ?'-':' '; 
	float tmpval =  (RealNum<0)? -RealNum : RealNum; 
	int intNum = tmpval ; 
	float tmpfrac = tmpval - intNum ;  
	int frac = tmpfrac * 100000 ;
	sprintf(str, "%c%d.%05d", tmpsign,intNum,frac);  
	
	LCD_SEND_A_STRING(str);  

} 
 
 



