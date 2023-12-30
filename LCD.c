                  
#include "lpc17xx.h"

/**********************************************************************************
#define RS (1<<29)	  
#define EN (1<<30)	  
#define LCD_Data (0XF)<<19
#define LCD_D0_Pin 19

unsigned char LCD_C=0,LCD_D=1,Wr_Data=1;

int Delay(unsigned int );

void Lcd_Init(void);
int Lcd_Data_Chr(unsigned char  ,unsigned char ,unsigned char ,unsigned char);  
int Lcd_Data_Str(unsigned char ,unsigned char ,unsigned char temp[]);
int Lcd_Wr(unsigned char );  
************************************************************************************/	



	
	


 
/*********************************************************************************

Lcd_Data_(0-cmd:1-data,line no,position,char to disp on LCD);

*********************************************************************************/
void Lcd_Init(void)
{     
unsigned char LCD_4bt_2_LINE=0x28;
unsigned char LCD_CLEAR=0X01;
unsigned char DISPLAY_ON=0X0F;
unsigned char LCD_CURSOR_OFF=0x0C;

Lcd_Data_Chr(0,0,0,0x83);
Lcd_Data_Chr(0,0,0,0x03);
Lcd_Data_Chr(0,0,0,0x82);
Lcd_Data_Chr(0,0,0,0x02);	

Lcd_Data_Chr(0,0,0,LCD_4bt_2_LINE);
Lcd_Data_Chr(0,0,0,DISPLAY_ON);
Lcd_Data_Chr(0,0,0,LCD_CLEAR);
Lcd_Data_Chr(0,0,0,LCD_CURSOR_OFF);	
Lcd_Data_Chr(0,0,0,0X06);
Delay(10);	
}

Lcd_Data_Chr(unsigned char RS1 ,unsigned char line,unsigned char position,unsigned char temp1) 
{
	
if(RS1==0)
{
Clear_Port0s=LCD_Data;
Set_Port0s= ((temp1>>4)<<LCD_D0_Pin)&LCD_Data;
Lcd_Wr(LCD_C);

Clear_Port0s=LCD_Data;
Set_Port0s= (temp1<<LCD_D0_Pin)&LCD_Data;
Lcd_Wr(LCD_C);
}

if(RS1==1)
{
if(line==1)
{
Clear_Port0s=LCD_Data;
Set_Port0s= ((0x7f+position>>4)<<LCD_D0_Pin)&LCD_Data;
Lcd_Wr(LCD_C);

Clear_Port0s=LCD_Data;
Set_Port0s= (0x7f+position<<LCD_D0_Pin)&LCD_Data;
Lcd_Wr(LCD_C);
}
if(line==2)
{
Clear_Port0s=LCD_Data;
Set_Port0s= ((0xbf+position>>4)<<LCD_D0_Pin)&LCD_Data;
Lcd_Wr(LCD_C);
	
Clear_Port0s=LCD_Data;
Set_Port0s= (0xbf+position<<LCD_D0_Pin)&LCD_Data;
Lcd_Wr(LCD_C);
}

Clear_Port0s=LCD_Data;
Set_Port0s= ((temp1>>4)<<LCD_D0_Pin)&LCD_Data;
Lcd_Wr(LCD_D);

Clear_Port0s=LCD_Data;
Set_Port0s= (temp1<<LCD_D0_Pin)&LCD_Data;
Lcd_Wr(LCD_D);
}		
}




///////////////////////////////////////////////////////////////////////////////

Lcd_Data_Str(unsigned char line1,unsigned char position,unsigned char temp[]) 
{

unsigned char t=0;	

if(line1==1)
{

Clear_Port0s=LCD_Data;
Set_Port0s= ((0x7f+position>>4)<<LCD_D0_Pin)&LCD_Data;
Lcd_Wr(LCD_C);


Clear_Port0s=LCD_Data;
Set_Port0s= (0x7f+position<<LCD_D0_Pin)&LCD_Data;
Lcd_Wr(LCD_C);
Delay(5);
}
if(line1==2)
{
	
Clear_Port0s=LCD_Data;
Set_Port0s= ((0xbf+position>>4)<<LCD_D0_Pin)&LCD_Data;
Lcd_Wr(LCD_C);

Clear_Port0s=LCD_Data;
Set_Port0s= (0xbf+position<<LCD_D0_Pin)&LCD_Data;
Lcd_Wr(LCD_C);
	
Delay(5);

}
while(temp[t]!='\0')
{		

Clear_Port0s=LCD_Data;
Set_Port0s= ((temp[t]>>4)<<LCD_D0_Pin)&LCD_Data;
Lcd_Wr(LCD_D);
	
Clear_Port0s=LCD_Data;
Set_Port0s= ((temp[t])<<LCD_D0_Pin)&LCD_Data;
Lcd_Wr(LCD_D);
t++;
}
t=0;
}



Lcd_Wr(unsigned char r)
{

if(r==1)
{
Set_Port0s= RS;
Set_Port0s= EN;
Delay(1);
Clear_Port0s= EN;
}

if(r==0)
{
Clear_Port0s= RS;
Set_Port0s= EN;
Delay(1);
Clear_Port0s= EN;
}
}


void Delay(unsigned int dtime)
{
unsigned int i,j;
for(i=0;i<dtime;i++)
for(j=0;j<25000;j++);
}


