/*
 * KEYBAD.c
 *
 * Created: 23/10/2019 10:20:13 ص
 * Author : mohamed khaled
 */  
#include "KEYBAD.h"  




int colunms[] = {C0 ,C1 , C2} ; 
int rows[] = {R0 ,R1 , R2} ;

void KeyPadInit (void){
	
	KeyPadDirection |= (1<<C0 | 1<<C1 |1<<C2 ) ;  
	KeyPadDirection &= ~(1<<R0 | 1<<R1 |1<<R2) ;  
	KeyPadPort = 0xff ; 
} 


char KeyPadgetkeypressed (void){
	
	int i , j ; 
	for (i = 0 ; i< 3 ; i++) 
	{ 
		KeyPadPort |= (1<<C0 | 1<<C1 | 1<<C2 ); 
		KeyPadPort &= ~(1<<colunms[i]); 
      for (j = 0;j<3;j++)
      {  
		  
		 if (!(KeyPadPin&(1<<rows[j])))  
		 {
		   while (!(KeyPadPin&(1<<rows[j])));
			 switch(i) 
			 { 
			      case (0):
			     { 
				 if(j==0) return '1' ;	
				 else if (j==1) return '4';
				 else if (j==2) return '7'; 
				 break; 
			     } 
				 
				 case (1):
			     { 
				 if(j==0) return '2' ;	
				 else if (j==1) return '5';
				 else if (j==2) return '8'; 
				 break; 
			     } 
				 
				 case (2):
			     { 
				 if(j==0) return '3' ;	
				 else if (j==1) return '6';
				 else if (j==2) return '9'; 
				 break; 
			     } 
			 
			  }
		 }       
       
	 }
	
   } 
   return 'A' ;
}