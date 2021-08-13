#include <delay.h>

bit m=0;

void keypad_init(void)
{
#define R1 PORTA.0
#define R2 PORTA.1
#define R3 PORTA.2
#define R4 PORTA.3
#define C1 PINA.4
#define C2 PINA.5
#define C3 PINA.6
#define C4 PINA.7

#define DDR_R1 DDRA.0
#define DDR_R2 DDRA.1
#define DDR_R3 DDRA.2
#define DDR_R4 DDRA.3
#define DDR_C1 DDRA.4
#define DDR_C2 DDRA.5
#define DDR_C3 DDRA.6
#define DDR_C4 DDRA.7

DDR_R1=1;
DDR_R2=1;
DDR_R3=1;
DDR_R4=1;
DDR_C1=0;
DDR_C2=0;
DDR_C3=0;
DDR_C4=0;

R1=0;
R2=0;
R3=0;
R4=0;
C1=1;
C2=1;
C3=1;
C4=1;

        PORTA.4=1;
        PORTA.5=1;
        PORTA.6=1;
        PORTA.7=1;

}


char read_key(void) 
{
 char key2=16;  
 
     R1=0;        R2=1;
     R3=1;        R4=1;
     delay_us(50);
     if(C1 == 0)   key2 = 7;    
else if(C2 == 0)   key2 = 8;
else if(C3 == 0)   key2 = 9;
else if(C4 == 0)   key2 = 12;
  
     R1=1;        R2=0;
     R3=1;        R4=1;
     delay_us(50);
     if(C1 == 0)   key2 = 4;   
else if(C2 == 0)   key2 = 5;
else if(C3 == 0)   key2 = 6;
else if(C4 == 0)   key2 = 13;
  
     R1=1;        R2=1;
     R3=0;        R4=1;
     delay_us(50);
     if(C1 == 0)   key2 = 1;    
else if(C2 == 0)   key2 = 2;
else if(C3 == 0)   key2 = 3;
else if(C4 == 0)   key2 = 14;
  
     R1=1;        R2=1;
     R3=1;        R4=0;
     delay_us(50);
     if(C1 == 0)   key2 = 10;    
else if(C2 == 0)   key2 = 0;
else if(C3 == 0)   key2 = 11;    
else if(C4 == 0)   key2 = 15;
     
 if(key2 == 16)   m=1;  
 return key2;  
 
}

/*
sprintf(st,"k: %d ",read_key());   
       lcd_gotoxy(0,0);
       lcd_puts(st);
       */