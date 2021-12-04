/*
 * SPI.h
 *
 * Created: 18/11/2019 10:18:49 م
 *  Author: mohamed khaled
 */ 
#include <avr/io.h>

#ifndef SPI_H_
#define SPI_H_

#define SPI_DDR DDRB  
#define SS 4
#define CLK 7
#define MISO 6
#define MOSI 5

enum SPI_CLOCK{
	FOSC4 = 0b00 ,
	FOSC16 = 0b01 ,
	FOSC64 = 0b10 ,
	FOSC128 = 0b11,
	FOSC2 = 0b100 ,
	FOSC8 = 0b101 ,
	FOSC32 = 0b110         
};
enum SPI_CLOCK_MODE {
	SPI_MODE0 = (0b00<<2),
	SPI_MODE1 = (0b01<<2),
	SPI_MODE2 = (0b10<<2),
	SPI_MODE3 = (0b11<<2)
};

enum SPI_DATA_ORDER {
	MSB_FIRST , LSB_FIRST 
};

enum SPI_SELECT {
	SPI_SLAVE = 0 , SPI_MASTER = 1 
	
};

enum SPI_EN {
	SPI_DISABLE , SPI_ENABLE
};

enum SPI_INTERRUPT {
	 SPI_INT_DISABLE , SPI_INT_ENABLE 
}; 

 struct config{
	enum SPI_CLOCK CLOCK ; 
	enum SPI_CLOCK_MODE  CLOCK_MODE; 
	enum SPI_DATA_ORDER DATA_ORDER; 
	enum SPI_SELECT MSSELECT ; 
	enum SPI_EN SPIENABLE ; 
	enum SPI_INTERRUPT INTERRUPT;
} ;

//---------------------------------------------------------------------------------------------------------
//APIS
void SPI_INIT(struct config CONFIG); 
unsigned char SPI_TRANSMIT (unsigned char data); 
unsigned char SPI_RECIEVE(unsigned char data); 


#endif /* SPI_H_ */