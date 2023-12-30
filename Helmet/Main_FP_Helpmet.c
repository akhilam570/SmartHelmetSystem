#include "lpc17xx.h"
#include "string.h"
#include "system_LPC17xx.c"
#include "Prj_Header.h"
#include "LCD.c"
#include "keypad_4x3.C"
#include "Serial_Uart0.c"
#include "Serial_Uart1.c"
#include "Serial_Uart2.c"
#include "fpm_ky_m8.c"
#include "s_card_256B.c"
#include "person1.c"
#include "person2.c"
#include "person3.c"
#include "app.c"


main()
{
	
SystemClockUpdate();
IO_Pins_Selection();	

Lcd_Init();
	
Init_UART0 (9600);
Init_UART1 (9600);
Init_UART2 (9600);	

//SmartCard_Init();
//UART2_TX_Str ("\r\n");	

FP_Init();
Enrolling_FPs(2);	

Project_Label();

while(1)
{

Lcd_Data_Chr(0,0,0,LCD_CLEAR);	
Lcd_Data_Str(1,1,"Pls Wear Your   ");
Lcd_Data_Str(2,1,"Helmet          ");
Delay(250);	
if(PinStatus_Port(1,28)==0)	
{
Lcd_Data_Chr(0,0,0,LCD_CLEAR);	
Lcd_Data_Str(1,1,"Press Button For");
Lcd_Data_Str(2,1,"Furthe Authentication");
Press_To_Enroll{	
Verify_Identify_Enroll();	
Check_Valid_Person1();	
}
}



}

}


void IO_Pins_Selection(void)
{
GPIO_Port1s_IODIR &=~(IR);	
GPIO_Port2s_IODIR &=~(coloums);
GPIO_Port2s_IODIR |=rows;
GPIO_Port0s_IODIR =(LCD_Data|RS|EN);
GPIO_Port3s_IODIR =Buzzzzz;	                     //output=1  // input=0


GPIO_Port0s|=Uart0|Uart2;	
GPIO_Port4s|=Uart1;
	
Buzzzzz_Off;
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
Lcd_Data_Chr(0,0,0,LCD_CLEAR);	
Lcd_Data_Str(1,1,"Pls Wear Your   ");
Lcd_Data_Str(2,1,"Helmet          ");

}



