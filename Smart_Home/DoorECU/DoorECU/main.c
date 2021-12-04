/*
 * DoorECU.c
 *
 * Created: 25/11/2021 01:58:33 م
 * Author : mohamed khaled
 */ 

#include <avr/io.h>  
#include <util/delay.h> 
#include <string.h> 

#include "KEYBAD.h" 
#include "LCD.h" 
#include "SPI.h" 

// initialization  
unsigned char X = NotPresssesd , Password[4] ; 
int counter , passLength = 4 ;  
//SPI configuration  
 struct config spi_config; 
 

int main(void)
{    
	
    spi_config.CLOCK = FOSC4;
    spi_config.CLOCK_MODE = SPI_MODE0 ;
    spi_config.DATA_ORDER = MSB_FIRST;
    spi_config.INTERRUPT = SPI_INT_DISABLE ;
    spi_config.MSSELECT = SPI_SLAVE ;
    spi_config.SPIENABLE = SPI_ENABLE ; 
	
	KeyPadInit();
	LCD_INIT(); 
	SPI_INIT(spi_config); 
	
	
	
    while (1) 
    {    
	    LCD_CLEAR(); 
		LCD_SEND_A_COMMAND(LCD_DISP_ON_CURSOR);
		LCD_SEND_A_STRING("Enter PassWord:");
		LCD_GOTO_XY(1,0); 
		X = KeyPadgetkeypressed(); 
		
		// get the entered password from the user  
		while(1){  
			X = KeyPadgetkeypressed(); 
			if (X != NotPresssesd)
			{
			 Password[counter] = X;  
			 LCD_SEND_A_CHAR(Password[counter]);  
			 counter++; 
			 if (counter == passLength)
			 {  
				 counter =0 ;
				 X = NotPresssesd; 
				 break;
			 }
			}
			 
		}
			
			
		LCD_CLEAR(); 
		LCD_SEND_A_STRING("Wait To Check"); 
		_delay_ms(10); 
		LCD_CLEAR();  
		
		
		// send the password to sensor ECU 
		int i; 
		for ( i = 0 ; i <4 ; i++)
		{ 
			char ACK = '1'; 
			ACK = SPI_TRANSMIT(Password[i]); 
			_delay_ms(1000); 
			LCD_SEND_A_CHAR(ACK); 
		}  
		
		
		
		
		// check the entered password 
		char flag = SPI_RECIEVE('A');  
		
		
		
		/*
		if (flag == 'A' )
		{ 
			LCD_SEND_A_STRING("Welcome"); 
			_delay_ms(10); 
			LCD_CLEAR(); 
		}
		else 
		{ 
			LCD_SEND_A_STRING("Wrong Try Again");
			_delay_ms(10);
			LCD_CLEAR();
		}
		*/
		
		
		  
		
		
		
		
    }
}

