#include <mega16.h>
#include <delay.h>
#include <stdio.h>
#include <stdlib.h> 
#include <alcd.h>
#include "Inc\keypad4x4.h" 

void micro_init(void);
void PID_Setting(void);
void SetPoint_Adj(void);


float kp , ki , kd;
float P_term , I_term , D_term , last_I_term;
unsigned long int encoder_int=0 , rpm , set_point=0;
long int error , last_error , PID_term , pid;
unsigned char data[5] , key , i=0 ,n; 
char st[33],str[33]; 
bit complete=0 , esc=0;

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
   encoder_int++;    
}

interrupt [TIM2_OVF] void timer2_ovf_isr(void)
{
             
    rpm = ((encoder_int*256) + TCNT0) * 3.75;       //    (x/64) *4*60
    encoder_int = 0;   TCNT0=0;  
    error = set_point - rpm;   
    
    P_term = kp * error;
    I_term = (ki * error) + last_I_term;
    D_term = (error - last_error) * kd;  
    
    PID_term = P_term + I_term + D_term;  
    pid = PID_term;
     if(PID_term < 1)     PID_term = 1;
     if(PID_term > 1023)  PID_term = 1023; 
    
    last_I_term = I_term;
    last_error = error;
    
   // OCR1A = PID_term; 
    
    printf("%04d\r",PID_term);
      
}

interrupt [USART_RXC] void usart_rx_isr(void)
{
}

void main(void)
{

 micro_init(); 
 lcd_clear();  
 #asm("sei")
 TCNT0=0x00;
 PORTD.6=0;   PORTD.4=1;
 
 while (1)
      {   
        OCR1A = PID_term;                                                            
        key = read_key();
  
        if(key==11)
        {
         lcd_clear(); 
         lcd_gotoxy(0,0);
         lcd_putsf("1:PID Setting\n2:Set Speed");   
         
         while(key!=1 && key!=2 && key!=10)
         key = read_key();     lcd_clear();
         if(key==1)        PID_Setting();
         if(key==2)        SetPoint_Adj();
        } 
         
        sprintf(str,"Set Point:%d\nRPM:%d   ",set_point,rpm);                 
        lcd_gotoxy(0,0);
        lcd_puts(str);  
        
        delay_ms(500);
      }
}

void PID_Setting(void)
{
 char s;
 float temp_data;
 
  for(s=0;s<3;s++)
  {
    lcd_clear();    
    lcd_gotoxy(0,0);
    switch(s)
    {
      case 0 : lcd_putsf("Kp:");  break;
      case 1 : lcd_putsf("Ki:");  break;
      case 2 : lcd_putsf("Kd:");  break; 
    } 
    
     complete=0;    i=0;   m=0;   
  
     while(complete==0)
     { 
      key = read_key();  
      if(key!=16 && m==1)
      {
        m=0;
        if(key<=9) 
        { data[i]=key;    if(i<4)  i++; }   
        else if(key==12)  {lcd_gotoxy(4+i,1); lcd_putsf(" ");  if(i>0)  i--;  complete=0;}  
        else if(key==11)  complete=1; 
                                           
        if(i>0 && key<=9)
        {
         lcd_gotoxy(4+i,1);
         sprintf(st,"%d",key); 
         lcd_puts(st);
        }
      }
      if(i==0) complete=0;
    
       if(complete==1)
       {  
        switch(i)
        {          
         case 0 : temp_data = 0;  break;
         case 1 : temp_data =  data[0];  break;
         case 2 : temp_data = (data[0]*10) + data[1];  break;  
         case 3 : temp_data = (data[0]*100) + (data[1]*10) + data[2];  break; 
         case 4 : temp_data = (data[0]*1000) + (data[1]*100) + (data[2]*10) + data[3];  break;  
        }
        lcd_clear();
        delay_ms(300);
       } 
     }    i=0;
      lcd_clear();      printf("%f\r",temp_data);
      
    switch(s)
    {
      case 0 : kp = temp_data/10000;  break;
      case 1 : ki = temp_data/10000;  break;
      case 2 : kd = temp_data/10000;  break; 
    }       printf("%f\r",kp);
  }  
}

void SetPoint_Adj(void)
{
 char z;
 
  lcd_clear();    
  lcd_gotoxy(0,0);
  lcd_putsf("Set Point:");
  
  complete=0;    i=0;   m=0;   
  
  while(complete==0)
  { 
   key = read_key();  
   if(key!=16 && m==1)
   {
     m=0;
     if(key<=9) 
     { data[i]=key;    if(i<4)  i++; }   
     else if(key==12)  {lcd_gotoxy(4+i,1); lcd_putsf(" ");  if(i>0)  i--;  complete=0;}  
     else if(key==11)  complete=1; 
    
     if(i>0 && key<=9)
     {
      lcd_gotoxy(4+i,1);
      sprintf(st,"%d",key); 
      lcd_puts(st);
     }
   }
    if(i==0) complete=0;
    
    if(complete==1)
    {  
      switch(i)
      {          
       case 0 : set_point = 0;  break;
       case 1 : set_point =  data[0];  break;
       case 2 : set_point = (data[0]*10) + data[1];  break;
       case 3 : set_point = (data[0]*100) + (data[1]*10) + data[2];  break;  
       case 4 : set_point = (data[0]*1000) + (data[1]*100) + (data[2]*10) + data[3];  break;    
      }
      lcd_clear();
      lcd_gotoxy(0,0);
      lcd_putsf("Thank You!");
       delay_ms(200);
    } 
 } i=0;
      lcd_clear();
}

void micro_init(void)
{
PORTA=0xF0;
DDRA=0x0F;
DDRD=0x70;
PORTB=0x01;

// Timer/Counter 0 initialization
// Clock source: T0 pin Falling Edge
// Mode: Normal top=0xFF
// OC0 output: Disconnected
TCCR0=0x06;
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 125.000 kHz
// Mode: Fast PWM top=0x03FF
// OC1A output: Non-Inv.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0x83;
TCCR1B=0x0B;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: TOSC1 pin
// Clock value: PCK2/32
// Mode: Normal top=0xFF
// OC2 output: Disconnected
ASSR=0x08;
TCCR2=0x03;
TCNT2=0x00;
OCR2=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x41;

// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: On
// USART Transmitter: On
// USART Mode: Asynchronous
// USART Baud Rate: 9600
UCSRA=0x00;
UCSRB=0x98;
UCSRC=0x86;
UBRRH=0x00;
UBRRL=0x33;
#asm("cli")

lcd_init(16);
keypad_init(); 
}