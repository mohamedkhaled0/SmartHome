/*
 * SensorECU.c
 *
 * Created: 29/11/2021 10:33:06 م
 * Author : mohamed khaled
 */ 

#include <avr/io.h> 
#include <util/delay.h>   
#include <string.h> 

#define F_CPU 8000000UL 
#include "SPI.h" 
#include "LCD.h" 

struct config spi_config;  


unsigned char Pass_Word[4];  
unsigned char RealPass[4] = "1234";

int main(void)
{
     spi_config.CLOCK = FOSC4;
     spi_config.CLOCK_MODE = SPI_MODE0 ;
     spi_config.DATA_ORDER = MSB_FIRST ;
     spi_config.INTERRUPT = SPI_INT_DISABLE ;
     spi_config.MSSELECT = SPI_MASTER ; 
     spi_config.SPIENABLE = SPI_ENABLE;
     
 
    SPI_INIT(spi_config); 
	LCD_INIT();  
	
    while (1) 
    {  
		int i ;  
		_delay_ms(40); 
		
		for ( i = 0 ; i <4; i++)
		{ 
			char ACK = '8'; 
			Pass_Word[i] = SPI_RECIEVE(ACK); 
			 
			
		}   
		
		LCD_SEND_A_STRING(Pass_Word); 
		
		
		/*
		if (!(strcmp(Pass_Word,RealPass)))
		{ 
			char ACK1 = SPI_TRANSMIT('A'); 
		} 
		*/ 
		
    }
}

