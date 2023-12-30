
#include "lpc17xx.h"



void Init_UART2 (unsigned int baud_rate); 
void UART2_TX_Chr (unsigned char ch);
char UART2_RX_Chr (void);
void UART2_TX_Str (unsigned char *str);
void Init_UART2_Interrupt(void);
void ISR_UART2(void)__irq;
void Delay(unsigned int);

unsigned int Divisor;
unsigned char rx_serial_data;

	
//Init_UART2(9600);

	
//UART2_TX_Str ("jai hanuman_28\r\n");




void Init_UART2 (unsigned int baud_rate)
{ 
uint32_t pclk;
LPC_SC->PCONP |= (1 << 24);
	
LPC_PINCON->PINSEL0	|= 0x00500000; 
pclk = SystemFrequency/4;
Divisor=pclk/(16*baud_rate);
LPC_UART2->LCR	= 0x00000083;   
LPC_UART2->DLL = Divisor%255;                            
LPC_UART2->DLM=  Divisor/255;                         
LPC_UART2->LCR	= 0x00000003;                           
}

                                                                                                                                                                                          		
void UART2_TX_Chr (unsigned char ch)  
{                
while (LPC_UART2->LSR == 0x20);
LPC_UART2->THR = ch;
//Delay(5);
}


void UART2_TX_Str (unsigned char *str)
{                 
while(*str!='\0')
{
while (LPC_UART2->LSR == 0x20);
LPC_UART2->THR = *str;
str++;
Delay(5);
}
}


char UART2_RX_Chr (void) 
{                    
while (!(LPC_UART2->LSR & 0x01));
return (LPC_UART2->RBR);
}

