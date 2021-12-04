/*
 * KEYPAD.h
 *
 * Created: 22/08/2019 03:50:47 ص
 *  Author: mohamed khaled
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <avr/io.h>
#include <util/delay.h>

#define R0 0 
#define R1 1 
#define R2 2  
#define C0 3 
#define C1 4 
#define C2 5 
#define NotPresssesd 'A'


#define KeyPadPort PORTA
#define KeyPadDirection DDRA
#define KeyPadPin PINA 

void KeyPadInit (void); 
char KeyPadgetkeypressed (void);


#endif /* KEYPAD_H_ */