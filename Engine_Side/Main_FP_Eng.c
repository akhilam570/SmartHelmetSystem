#include "lpc17xx.h"
#include "Prj_Header.h"
#include "LCD.c"
#include "Serial_Uart1.c"
#include "Serial_Uart2.c"
#include "fpm_ky_m8.c"

unsigned char rxd;

main()
{
	
SystemClockUpdate();
IO_Pins_Selection();	

Lcd_Init();
	
Init_UART0 (9600);
Init_UART1 (9600);
Init_UART2 (9600);	

Project_Label();

while(1)
{
rxd=UART2_RX_Chr();	
if(rxd=='1')	
{
Lcd_Data_Chr(0,0,0,LCD_CLEAR);	
Lcd_Data_Str(1,1,"Authentication Ok");
Lcd_Data_Str(2,1,"Person:1         ");
Set_Port3s= IR;		
	
}
if(rxd=='2')	
{
Lcd_Data_Chr(0,0,0,LCD_CLEAR);	
Lcd_Data_Str(1,1,"Authentication Ok");
Lcd_Data_Str(2,1,"Person:2         ");
Set_Port3s= IR;	
}

if(rxd=='0')	
{
Lcd_Data_Chr(0,0,0,LCD_CLEAR);	
Lcd_Data_Str(1,1,"Helmet Removed");
Clear_Port3s= IR;
Buzzzzz_On;
Delay(500);
Buzzzzz_Off;
	
}

}



}



void IO_Pins_Selection(void)
{
//GPIO_Port1s_IODIR |=(IR);	
GPIO_Port2s_IODIR &=~(coloums);
GPIO_Port2s_IODIR |=rows;
GPIO_Port0s_IODIR =(LCD_Data|RS|EN);
GPIO_Port3s_IODIR =(Buzzzzz|IR);	                     //output=1  // input=0


GPIO_Port0s|=Uart0|Uart2;	
GPIO_Port4s|=Uart1;
	
Buzzzzz_Off;
Clear_Port3s= IR;	
}



PinStatus_Port(unsigned char port,unsigned int pin)
{
if(port==0)
{
x=(Port0_Status&(1<<pin))?1:0;
}
if(port==1)
{
x=(Port1_Status&(1<<pin))?1:0;
}
if(port==2)
{
x=(Port2_Status&(1<<pin))?1:0;
}	
if(port==3)
{
x=(Port3_Status&(1<<pin))?1:0;
}
return x;
}



void Project_Label(void)
{
Lcd_Data_Str(1,1,"XBEE -F.P Based");
Lcd_Data_Str(2,1,"Smart-Helmet   ");
Delay(time);
//Lcd_Data_Chr(0,0,0,LCD_CLEAR);	
//Lcd_Data_Str(1,1,"Pls Wear Your   ");
//Lcd_Data_Str(2,1,"Helmet          ");

}



