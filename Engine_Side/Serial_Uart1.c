
#include "lpc17xx.h"


/*****************************************************
void Init_UART1 (unsigned int baud_rate); 
void UART1_TX_Chr (unsigned char ch);
char UART1_RX_Chr (void);
void UART1_TX_Str (unsigned char *str);
void Init_UART1_Interrupt(void);
void ISR_UART1(void)__irq;
void Delay(unsigned int);

unsigned int Divisor;
unsigned char rx_serial_data;

******************************************************/





void Init_UART1 (unsigned int baud_rate)
{ 
uint32_t pclk;


pclk = SystemFrequency/4;
Divisor=pclk/(16*baud_rate);
LPC_UART1->LCR	= 0x00000083;   
LPC_UART1->DLL = Divisor%255;                            
LPC_UART1->DLM=  Divisor/255;                         
LPC_UART1->LCR	= 0x00000003;                           
}

                                                                                                                                                                                          		
void UART1_TX_Chr (unsigned char ch)  
{                
while (LPC_UART1->LSR == 0x20);
LPC_UART1->THR = ch;
//Delay(5);
}


void UART1_TX_Str (unsigned char *str)
{                 
while(*str!='\0')
{
while (LPC_UART1->LSR == 0x20);
LPC_UART1->THR = *str;
str++;
Delay(5);
}
}


char UART1_RX_Chr (void) 
{                    
while (!(LPC_UART1->LSR & 0x01));
return (LPC_UART1->RBR);
}

