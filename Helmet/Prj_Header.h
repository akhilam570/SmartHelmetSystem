#include "lpc17xx.h"

/**************************************************/
#define time 2000

/******************************************************************************************************/
//output---->devices

#define Buzzzzz             (1<<25)

#define Buzzzzz_On          Set_Port3s= Buzzzzz;
#define Buzzzzz_Off         Clear_Port3s= Buzzzzz;

/******************************************************************************************************/

//#define Press_To_Enroll  while(PinStatus_Port(1,29)!=0);	 //wait for active low
#define Press_To_Chk_Erl  while(Keypad_Reading()!='1');



/******************************************************************************************************/



#define GPIO_Port0s  LPC_PINCON->PINSEL0	
#define GPIO_Port4s  LPC_PINCON->PINSEL4 


#define GPIO_Port0s_IODIR    LPC_GPIO0->FIODIR 
#define Port0_Status         LPC_GPIO0->FIOPIN 
#define Set_Port0s           LPC_GPIO0->FIOSET                      
#define Clear_Port0s         LPC_GPIO0->FIOCLR  

#define GPIO_Port1s_IODIR    LPC_GPIO1->FIODIR 
#define Port1_Status         LPC_GPIO1->FIOPIN 
#define Set_Port1s           LPC_GPIO1->FIOSET                      
#define Clear_Port1s         LPC_GPIO1->FIOCLR                       

#define GPIO_Port2s_IODIR    LPC_GPIO2->FIODIR 
#define Port2_Status         LPC_GPIO2->FIOPIN 
#define Set_Port2s           LPC_GPIO2->FIOSET                      
#define Clear_Port2s         LPC_GPIO2->FIOCLR      

#define GPIO_Port3s_IODIR    LPC_GPIO3->FIODIR 
#define Port3_Status         LPC_GPIO3->FIOPIN 
#define Set_Port3s           LPC_GPIO3->FIOSET                      
#define Clear_Port3s         LPC_GPIO3->FIOCLR                       

/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
# define Uart0 (0x5<<4) //pinsel-0 //pin no:P0.2 (txd0)---P0.3 (rxd0)
# define Uart1 (0xA<<0) //pinsel-4 //pin no:P2.0 (txd1)---P2.1 (rxd1)
# define Uart2 (0x5<<20)//pinsel-0 //pin no:P0.10(txd2)---P0.11(rxd2)
# define Uart3 (0xF<<24)//pinsel-9 //pin no:P4.28(txd3)---P4.29(rxd3)


#define  Ext_Int0	  (0x1<<20) //pin no:P2.10
#define  Ext_Int1   (0x1<<22) //pin no:P2.11
#define  Ext_Int2   (0x1<<24) //pin no:P2.12
#define  Ext_Int3   (0x1<<26) //pin no:P2.13   //these four present in pinsel4


#define  ADC0_Volt	 (0x1<<14)   //pin no:P0.23
#define  ADC1_Ldrs   (0x1<<16)   //pin no:P0.24
#define  ADC2_Humi   (0x1<<18)   //pin no:P0.25
#define  ADC3_Temp   (0x1<<20)   //pin no:P0.26 //these four present in pinsel1

#define  ADC4_Rsrv   (0x3UL<<28) //pin no:P0.30
#define  ADC5_Rsrv   (0x3UL<<30) //pin no:P0.31 // these two present in pinsel3


#define  I2C0	 (0x5<<22) //pin no:P0.27(SDA0)---P0.28(CLK0) //pinsel-1
#define  I2C1  (0xF<<0)  //pin no:P0.0 (SDA1)---P0.1 (CLK1) //pinsel-0
#define  I2C2  (0xA<<20) //pin no:P0.10(SDA2)---P0.11(CLK2) //pinsel-0

/**********************************************************************************/

/***************************LCD Functions*************************************/
#define RS (1<<21)	  
#define EN (1<<22)	  
#define LCD_Data (0XF)<<23
#define LCD_D0_Pin 23

#define IR (1<<28)


unsigned char LCD_C=0,LCD_D=1,Wr_Data=1;

void Delay(unsigned int );
void Lcd_Init(void);
int Lcd_Data_Chr(unsigned char  ,unsigned char ,unsigned char ,unsigned char);  
int Lcd_Data_Str(unsigned char ,unsigned char ,unsigned char temp[]);
int Lcd_Wr(unsigned char );  

/*****************************************************************************/
/************************Serial Communication(UART0)**************************/
void Init_UART0 (unsigned int baud_rate); 
void UART0_TX_Chr (unsigned char ch);
char UART0_RX_Chr (void);
void UART0_TX_Str (unsigned char *str);

unsigned int Divisor;

/*****************************************************************************/
/************************Serial Communication(UART1)**************************/

void Init_UART1 (unsigned int baud_rate); 
void UART1_TX_Chr (unsigned char ch);
char UART1_RX_Chr (void);
void UART1_TX_Str (unsigned char *str);
void Init_UART1_Interrupt(void);
void ISR_UART1(void)__irq;
void Delay(unsigned int);
/*****************************************************************************/
void Project_Label(void);
void IO_Pins_Selection(void);


void SmartCard_Authentication(void);
void Finger_Print_Enrolling(void);

int PinStatus_Port(unsigned char ,unsigned int);

unsigned char x,No_FPs;
unsigned char License_Expired=0;
unsigned char bank_selected;

