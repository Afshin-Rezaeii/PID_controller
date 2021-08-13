/*
 BMS Project
 Setting
 Change Password ,... functions
 Created : 1393/04/8  19:10
*/ 

eeprom unsigned char password[4];
flash unsigned char pass_admin[]={1,2,3,4}; 
unsigned char data[5] , key , i=0 , pass[4] ,n;     
unsigned int address;
char str[21];
bit complete=0 , esc=0;
bit pass_true_flag=0;
bit Lock;

void beep(void);
void reset_var(void);
void get_pass(void);
void change_pass(void);
void get_init(void);
void setting(void);
int array4_to_Dec(char *array);

int array4_to_Dec(char *array)
{ 
 int answer;
 char i;
  
  answer = (array[0]*1000) + (array[1]*100) + (array[2]*10) + array[3]; 
  return answer;
}

void change_pass(void)
{
 char z , st[10];
 
  lcd_clear();    
  lcd_gotoxy(0,0);
  lcd_putsf("New Pass:");
  
  complete=0;    i=0;   m=0;    beep();
  
 while(complete==0)
 { 
   key = read_key();  
   if(key!=16 && m==1)
   {
     beep();    m=0;
     if(key<=9) 
     { data[i]=key;    if(i<4)  i++; }   
     else if(key==10)  {lcd_gotoxy(4+i,1); lcd_putsf(" ");  if(i>0)  i--;  complete=0;}  
     else if(key==15)  complete=1; 
    
     if(i>0)
     {
      lcd_gotoxy(4+i,1);
      sprintf(st,"%c",'*'); 
      lcd_puts(st);
     }
   }
    if(i==0) complete=0; 
   
    if(complete==1)
    {
     for(z=0; z<4; z++)
     {
      password[z] = data[z]; 
     }      
     for(n=0; n<4; n++)   pass[n] = password[n];
     
      lcd_clear();
      lcd_gotoxy(0,0);
      lcd_putsf("Pass Changed");
       delay_ms(1000);
    } 
 } i=0;
      lcd_clear();
}

void get_pass(void)
{   
 int data_passord[10]; 
 char st[10];   
 complete=0; 
    
  lcd_clear();
  lcd_gotoxy(0,0);
  lcd_putsf("Enter Pass:");

 while(pass_true_flag == 0)
 {
  key = read_key();  
   if(key!=16 && m==1)
   {
     beep();   m=0;
     if(key<=9) 
     { data_passord[i]=key;    if(i<8)  i++; }   
     else if(key==10)  {lcd_gotoxy(6+i,1); lcd_putsf(" ");  if(i>0)  i--;}  
     else if(key==15)   complete=1; 
    
     if(i>0)
     {
      lcd_gotoxy(6+i,1);
      sprintf(st,"%c",'*');  
      lcd_puts(st);
     }
   }
   
   if(complete==1)
   {
    if((data_passord[0]==pass_admin[0] && data_passord[1]==pass_admin[1] && data_passord[2]==pass_admin[2] && data_passord[3]==pass_admin[3]) || (data_passord[0]==password[0] && data_passord[1]==password[1] && data_passord[2]==password[2] && data_passord[3]==password[3]))
    {
     pass_true_flag=1;
     lcd_clear();
     lcd_gotoxy(1,1);
     lcd_putsf("* Welcome *");
     delay_ms(700);  
     for(n=0; n<4; n++)   pass[n] = password[n];    Lock=0;
    }
    else
    {
     pass_true_flag=0;        
     complete = 0;
     lcd_clear();
     lcd_gotoxy(2,1);
     lcd_putsf("Pass False");
      delay_ms(700);
     lcd_clear();
     lcd_gotoxy(0,0);
     lcd_putsf("Enter Pass:");     Lock=1;
    }     
    i=0;
   }
 }
 lcd_clear();    pass_true_flag=0;    data_passord[0]=0;   data_passord[1]=0;   data_passord[2]=0;   data_passord[3]=0;
}

void reset_var(void)
{
  complete=0;   esc=0;   i=0;   key=16; 
}

void beep(void)
{
  //buzzer = ON;
  delay_ms(60);
  //buzzer = OFF;
}
/*
void setting(void)
{   
  beep();         
  while(key==14)   
   key = read_key();   
   change_pass();    
   lcd_clear();   lcd_gotoxy(2,1);     lcd_putsf("** Thank You **");    delay_ms(1000);    lcd_clear(); 
   reset_cpu();
} */

void setting(void)
{   
  beep();         
  while(key==15)   
   key = read_key();   
  
  get_pass();   key=16;
       
  lcd_clear();   
  lcd_gotoxy(0,0);   lcd_putsf("1://Lamp ON|2://Lamp OFF");
  lcd_gotoxy(0,1);   lcd_putsf("3://Door ON|4://Door OFF");
  lcd_gotoxy(0,2);   lcd_putsf("5: Change Password  ");
  
  while(key!=15 && key!=10)
  {  
    key = read_key();   
    if(key==1)   //Lamp = ON;
    if(key==2)   //Lamp = OFF;
    if(key==3)   //Door = ON;
    if(key==4)   //Door = OFF;  
    if(key==5)   change_pass();
  }             
   lcd_clear();   lcd_gotoxy(2,1);     lcd_putsf("** Thank You **");    delay_ms(1000);    lcd_clear(); 
}
