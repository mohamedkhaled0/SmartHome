/*
 * SPI.c
 *
 * Created: 18/11/2019 10:19:03 م
 *  Author: mohamed khaled
 */
#include "SPI.h" 


struct config GLOBAL_SPI_CONFIG ; 

static void (*SPI_isr)(void) ; 

void SPI_INIT(struct config CONFIG){ 
	
	GLOBAL_SPI_CONFIG = CONFIG ; 
	
	//Set Clock Mode  
    SPCR |= GLOBAL_SPI_CONFIG.CLOCK_MODE; 
	
	
	//Set  Clock 
	if ((GLOBAL_SPI_CONFIG.CLOCK == FOSC4) || (GLOBAL_SPI_CONFIG.CLOCK ==FOSC16 )|| (GLOBAL_SPI_CONFIG.CLOCK ==FOSC64 )||(GLOBAL_SPI_CONFIG.CLOCK ==FOSC128))
	{ 
		SPCR |= (GLOBAL_SPI_CONFIG.CLOCK) ; 
	}
   else if ((GLOBAL_SPI_CONFIG.CLOCK == FOSC2) || (GLOBAL_SPI_CONFIG.CLOCK ==FOSC8 )|| (GLOBAL_SPI_CONFIG.CLOCK ==FOSC32 ))
	{ 
		SPCR |= (GLOBAL_SPI_CONFIG.CLOCK&(0b11)) ;  
		SPSR |=(1<<SPI2X);
	} 
	
	
	// SPI MASTER / SLAVE SELECT  
	if (GLOBAL_SPI_CONFIG.MSSELECT == SPI_MASTER) {
          SPCR |=(1<<4); 
		  SPI_DDR |= (1<<MOSI) | (1<<SS) | (1<<CLK) ; 
		  SPI_DDR &= ~(1<<MISO); 
    }
    else if (GLOBAL_SPI_CONFIG.MSSELECT == SPI_SLAVE) {
	      SPCR &= ~(1<<4); 
		  SPI_DDR |= (1<<MISO);  
		  SPI_DDR &= ~(1<<MOSI) & ~(1<<SS) & ~(1<<CLK) ;
		   
		    
	}
	
	//SPI DATA ORDER  
	if (GLOBAL_SPI_CONFIG.DATA_ORDER == LSB_FIRST) {SPCR|=(1<<DORD);}
	else if (GLOBAL_SPI_CONFIG.DATA_ORDER == MSB_FIRST) { SPCR &= ~(1<<DORD);}
	
	// SPI INTERRUPT ENABLE 
	if (GLOBAL_SPI_CONFIG.INTERRUPT == SPI_INT_ENABLE) {SPCR|=(1<<SPIE);}
	else if (GLOBAL_SPI_CONFIG.INTERRUPT == SPI_INT_DISABLE) {SPCR &= ~(1<<SPIE);} 
	
	// SPI ENABLE 
	if (GLOBAL_SPI_CONFIG.MSSELECT == SPI_ENABLE) {SPCR|=(1<<6);}
    else if (GLOBAL_SPI_CONFIG.MSSELECT == SPI_DISABLE) {SPCR &= ~(1<<6);} 
	
} 





unsigned char SPI_TRANSMIT (unsigned char data){ 
	
	SPDR = data; 
	while (!(SPSR &(1<<SPIF))); 
	return SPDR ; 
	
}

unsigned char SPI_RECIEVE(unsigned char data){ 
	
	SPDR = data; 
	while (!(SPSR &(1<<SPIF))); 
	return SPDR ; 
	
} 



void SPI_CALL_BACK_FUN (void (ptr_to_isr)(void)){
	SPI_isr = ptr_to_isr ; 
} 



ISR(SPI_STC_VECT){
	SPI_isr(); 
}