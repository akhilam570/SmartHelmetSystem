#include "lpc17xx.h"

void Check_Valid_Person1(void);
void Person1_Banking_Process(void);

void P1B1_Process(void);
void P1B2_Process(void);
void P1B3_Process(void);

void P1B1_Cash_Withdraw(void);
void P1B2_Cash_Withdraw(void);
void P1B3_Cash_Withdraw(void);

void P1B1_Enter_Amt(void);
void P1B2_Enter_Amt(void);
void P1B3_Enter_Amt(void);


unsigned char P1B1_Balance_Amt[6],P1B1_Withdraw_Amt[6],P1B1_Send_Bal_Cash[6];
unsigned char P1B2_Balance_Amt[6],P1B2_Withdraw_Amt[6],P1B2_Send_Bal_Cash[6];
unsigned char P1B3_Balance_Amt[6],P1B3_Withdraw_Amt[6],P1B3_Send_Bal_Cash[6];

unsigned int d11,d22,d33,d44,d55;

unsigned int P1B1_Balance_Cash,P1B1_Withdraw_Cash;
unsigned int P1B2_Balance_Cash,P1B2_Withdraw_Cash;
unsigned int P1B3_Balance_Cash,P1B3_Withdraw_Cash;


void Check_Valid_Person1(void)
{
Lcd_Data_Chr(0,0,0,LCD_CLEAR);	
Lcd_Data_Str(1,1,"Checking Fprint.");
if(serial_data[9]==0x01)    //1
{
Lcd_Data_Str(1,1,"Name:F.P-1      ");
Lcd_Data_Str(2,1,"Authntication Ok");
Delay(time);
UART2_TX_Str ("1");	
serial_data[9]=0x00;	
while(1)
{
Lcd_Data_Chr(0,0,0,LCD_CLEAR);	
Lcd_Data_Str(2,1,"Helmet Okay     ");
Delay(250);	
if(PinStatus_Port(1,28)==1)	
{	
Lcd_Data_Chr(0,0,0,LCD_CLEAR);	
Lcd_Data_Str(2,1,"Helmet Removed");
Delay(5000);	
UART2_TX_Str ("0");	
break;	

}	
}
}
else if(serial_data[9]==0x02)    //2
{
Lcd_Data_Str(1,1,"Name:F.P-2      ");
Lcd_Data_Str(2,1,"Authntication Ok");
Delay(time);
UART2_TX_Str ("2");	
serial_data[9]=0x00;
while(1)
{
Lcd_Data_Chr(0,0,0,LCD_CLEAR);	
Lcd_Data_Str(2,1,"Helmet Okay     ");
Delay(250);	
if(PinStatus_Port(1,28)==1)	
{	
Lcd_Data_Chr(0,0,0,LCD_CLEAR);	
Lcd_Data_Str(2,1,"Helmet Removed");
Delay(5000);	
UART2_TX_Str ("0");	
break;	
}	
}
}

else
{
Lcd_Data_Str(1,1,"F-Print Mismatch");
Lcd_Data_Str(2,1,"Plc Chk Again...");
Delay(time);
UART2_TX_Str ("0");		
}	
}

/**************************************************************************************
***************************************************************************************/
void Person1_Banking_Process(void)
{
//unsigned int ptr;
while(1)
{
Lcd_Data_Chr(0,0,0,LCD_CLEAR);	
Lcd_Data_Str(1,1,"1.Bank1  2.Bank2");
Lcd_Data_Str(2,1,"3.Bank3 '#'-Exit");
bank_selected=Keypad_Reading();

if((bank_selected=='1'))
{
Lcd_Data_Str(1,1,"Bank-1 Selected");
Lcd_Data_Str(2,1,"    Welcome    ");
Delay(500);
P1B1_Process();	
}
else if((bank_selected=='2'))
{
Lcd_Data_Str(1,1,"Bank-2 Selected");
Lcd_Data_Str(2,1,"    Welcome    ");
Delay(500);
P1B2_Process();
}
else if((bank_selected=='3'))
{
Lcd_Data_Str(1,1,"Bank-3 Selected");
Lcd_Data_Str(2,1,"    Welcome    ");
Delay(500);
P1B3_Process();
}
else if((bank_selected=='#'))
{
Lcd_Data_Str(1,1,"   Thank You   ");
Lcd_Data_Str(2,1,"Transtn Compltd");
Delay(500);
break;	
}

else 
{
Lcd_Data_Str(1,1,"In Valid K-Press");
Lcd_Data_Str(2,1,"      Sorry     ");
Delay(350);
}
}	
}
/*--------------------------------------------------------------------------------------
                               Person1-Bank1 process
---------------------------------------------------------------------------------------*/
void P1B1_Process(void)
{
UART2_TX_Str("0P1B1");
while(1)
{
Lcd_Data_Chr(0,0,0,LCD_CLEAR);	
Lcd_Data_Str(1,1,"1.Balance Enqry");
Lcd_Data_Str(2,1,"2.Cash Withdraw");
	
bank_selected=Keypad_Reading();

if((bank_selected=='1'))
{
Lcd_Data_Chr(0,0,0,LCD_CLEAR);	
Lcd_Data_Str(1,1,"Bank-1 Checking");
Lcd_Data_Str(2,1,"Balance........");
Delay(500);
UART2_TX_Str("P1B1B");	
for(count=0;count<5;count++)
{
P1B1_Balance_Amt[count]=UART2_RX_Chr();
}
Lcd_Data_Chr(0,0,0,LCD_CLEAR);
Lcd_Data_Str(1,1,"Bank-1 Balance ");
Lcd_Data_Str(2,12,P1B1_Balance_Amt);
Delay(1000);
Lcd_Data_Str(1,1,"Baln Transaction");
Lcd_Data_Str(2,1,"Completed Thanq ");
Delay(500);
Lcd_Data_Str(1,1,"SCard -F.P Based");
Lcd_Data_Str(2,1,"MultiAcc ATM Crd");
Delay(500);
break;
}
else if((bank_selected=='2'))
{
Lcd_Data_Chr(0,0,0,LCD_CLEAR);	
Lcd_Data_Str(1,1,"Bank-1 Checking");
Lcd_Data_Str(2,1,"For Process....");
Delay(500);
P1B1_Cash_Withdraw();
Lcd_Data_Str(1,1,"WTDL Transaction");
Lcd_Data_Str(2,1,"Completed Thanq ");
Delay(500);
Lcd_Data_Str(1,1,"SCard -F.P Based");
Lcd_Data_Str(2,1,"MultiAcc ATM Crd");
break;
}
else 
{
Lcd_Data_Str(1,1,"In Valid K-Press");
Lcd_Data_Str(2,1,"      Sorry     ");
Delay(350);
}
}	
}

void P1B1_Cash_Withdraw(void)
{
UART2_TX_Str("P1B1W");	

for(count=0;count<5;count++)
{
P1B1_Balance_Amt[count]=UART2_RX_Chr();
}
Lcd_Data_Chr(0,0,0,LCD_CLEAR);
Lcd_Data_Str(1,1,"Bank-1 Balance ");
Lcd_Data_Str(2,12,P1B1_Balance_Amt);
Delay(1300);
d11=(P1B1_Balance_Amt[0]-48);
d22=(P1B1_Balance_Amt[1]-48);
d33=(P1B1_Balance_Amt[2]-48);
d44=(P1B1_Balance_Amt[3]-48);
d55=(P1B1_Balance_Amt[4]-48);

P1B1_Balance_Cash=(d11*10000)+(d22*1000)+(d33*100)+(d44*10)+d55;
P1B1_Enter_Amt();
}


void P1B1_Enter_Amt(void)
{
unsigned int ptr;
ptr=3;
Lcd_Data_Chr(0,0,0,LCD_CLEAR);
Lcd_Data_Str(1,1,"Enter Amount    ");
for(i=0;i<5;i++)
{
P1B1_Withdraw_Amt[i]=Keypad_Reading();
Lcd_Data_Chr(1,2,ptr++,P1B1_Withdraw_Amt[i]);
Delay(250);
}

d11=(P1B1_Withdraw_Amt[0]-48);
d22=(P1B1_Withdraw_Amt[1]-48);
d33=(P1B1_Withdraw_Amt[2]-48);
d44=(P1B1_Withdraw_Amt[3]-48);
d55=(P1B1_Withdraw_Amt[4]-48);

P1B1_Withdraw_Cash=(d11*10000)+(d22*1000)+(d33*100)+(d44*10)+d55;

if(P1B1_Balance_Cash>=P1B1_Withdraw_Cash)
{
Lcd_Data_Str(1,1,"Amount Deducting");
Lcd_Data_Str(2,1,"Please Wait.....");	
P1B1_Balance_Cash=P1B1_Balance_Cash-P1B1_Withdraw_Cash;
Delay(1500);
Lcd_Data_Chr(0,0,0,LCD_CLEAR);	
Lcd_Data_Str(1,1,"Remain Balance  ");	
P1B1_Send_Bal_Cash[0]=(P1B1_Balance_Cash/10000)+'0';	//5
P1B1_Send_Bal_Cash[1]=((P1B1_Balance_Cash%10000)/1000)+'0';//4
P1B1_Send_Bal_Cash[2]=(((P1B1_Balance_Cash%10000)%1000)/100)+'0';//3	
P1B1_Send_Bal_Cash[3]=((((P1B1_Balance_Cash%10000)%1000)%100)/10)+'0';//2
P1B1_Send_Bal_Cash[4]=((((P1B1_Balance_Cash%10000)%1000)%100)%10)+'0';//1
Lcd_Data_Str(2,12,P1B1_Send_Bal_Cash);	
Delay(1500);
UART2_TX_Str (P1B1_Send_Bal_Cash);
}
else
{
Lcd_Data_Str(1,1,"Unable To Process");
Lcd_Data_Str(2,1,"Low Balance      ");
Delay(500);
}
}
/*=====================================================================================*/

/*--------------------------------------------------------------------------------------
                               Person1-Bank2 process
---------------------------------------------------------------------------------------*/
void P1B2_Process(void)
{
UART2_TX_Str("0P1B2");
while(1)
{
Lcd_Data_Chr(0,0,0,LCD_CLEAR);	
Lcd_Data_Str(1,1,"1.Balance Enqry");
Lcd_Data_Str(2,1,"2.Cash Withdraw");
	
bank_selected=Keypad_Reading();

if((bank_selected=='1'))
{
Lcd_Data_Chr(0,0,0,LCD_CLEAR);	
Lcd_Data_Str(1,1,"Bank-2 Checking");
Lcd_Data_Str(2,1,"Balance........");
Delay(500);
UART2_TX_Str("P1B2B");	
for(count=0;count<5;count++)
{
P1B2_Balance_Amt[count]=UART2_RX_Chr();
}
Lcd_Data_Chr(0,0,0,LCD_CLEAR);
Lcd_Data_Str(1,1,"Bank-2 Balance ");
Lcd_Data_Str(2,12,P1B2_Balance_Amt);
Delay(1000);
Lcd_Data_Str(1,1,"Baln Transaction");
Lcd_Data_Str(2,1,"Completed Thanq ");
Delay(500);
Lcd_Data_Str(1,1,"SCard -F.P Based");
Lcd_Data_Str(2,1,"MultiAcc ATM Crd");
Delay(500);
break;
}
else if((bank_selected=='2'))
{
Lcd_Data_Chr(0,0,0,LCD_CLEAR);	
Lcd_Data_Str(1,1,"Bank-2 Checking");
Lcd_Data_Str(2,1,"For Process....");
Delay(500);
P1B2_Cash_Withdraw();
Lcd_Data_Str(1,1,"WTDL Transaction");
Lcd_Data_Str(2,1,"Completed Thanq ");
Delay(500);
Lcd_Data_Str(1,1,"SCard -F.P Based");
Lcd_Data_Str(2,1,"MultiAcc ATM Crd");
break;
}
else 
{
Lcd_Data_Str(1,1,"In Valid K-Press");
Lcd_Data_Str(2,1,"      Sorry     ");
Delay(350);
}
}	
}

void P1B2_Cash_Withdraw(void)
{
UART2_TX_Str("P1B2W");	

for(count=0;count<5;count++)
{
P1B2_Balance_Amt[count]=UART2_RX_Chr();
}
Lcd_Data_Chr(0,0,0,LCD_CLEAR);
Lcd_Data_Str(1,1,"Bank-2 Balance ");
Lcd_Data_Str(2,12,P1B2_Balance_Amt);
Delay(1300);
d11=(P1B2_Balance_Amt[0]-48);
d22=(P1B2_Balance_Amt[1]-48);
d33=(P1B2_Balance_Amt[2]-48);
d44=(P1B2_Balance_Amt[3]-48);
d55=(P1B2_Balance_Amt[4]-48);

P1B2_Balance_Cash=(d11*10000)+(d22*1000)+(d33*100)+(d44*10)+d55;
P1B2_Enter_Amt();
}


void P1B2_Enter_Amt(void)
{
unsigned int ptr;
ptr=3;
Lcd_Data_Chr(0,0,0,LCD_CLEAR);
Lcd_Data_Str(1,1,"Enter Amount    ");
for(i=0;i<5;i++)
{
P1B2_Withdraw_Amt[i]=Keypad_Reading();
Lcd_Data_Chr(1,2,ptr++,P1B2_Withdraw_Amt[i]);
Delay(250);
}

d11=(P1B2_Withdraw_Amt[0]-48);
d22=(P1B2_Withdraw_Amt[1]-48);
d33=(P1B2_Withdraw_Amt[2]-48);
d44=(P1B2_Withdraw_Amt[3]-48);
d55=(P1B2_Withdraw_Amt[4]-48);

P1B2_Withdraw_Cash=(d11*10000)+(d22*1000)+(d33*100)+(d44*10)+d55;

if(P1B2_Balance_Cash>=P1B2_Withdraw_Cash)
{
Lcd_Data_Str(1,1,"Amount Deducting");
Lcd_Data_Str(2,1,"Please Wait.....");	
P1B2_Balance_Cash=P1B2_Balance_Cash-P1B2_Withdraw_Cash;
Delay(1500);
Lcd_Data_Chr(0,0,0,LCD_CLEAR);	
Lcd_Data_Str(1,1,"Remain Balance  ");	
P1B2_Send_Bal_Cash[0]=(P1B2_Balance_Cash/10000)+'0';	//5
P1B2_Send_Bal_Cash[1]=((P1B2_Balance_Cash%10000)/1000)+'0';//4
P1B2_Send_Bal_Cash[2]=(((P1B2_Balance_Cash%10000)%1000)/100)+'0';//3	
P1B2_Send_Bal_Cash[3]=((((P1B2_Balance_Cash%10000)%1000)%100)/10)+'0';//2
P1B2_Send_Bal_Cash[4]=((((P1B2_Balance_Cash%10000)%1000)%100)%10)+'0';//1
Lcd_Data_Str(2,12,P1B2_Send_Bal_Cash);	
Delay(1500);
UART2_TX_Str (P1B2_Send_Bal_Cash);
}
else
{
Lcd_Data_Str(1,1,"Unable To Process");
Lcd_Data_Str(2,1,"Low Balance      ");
Delay(500);
}
}
/*=====================================================================================*/
/*--------------------------------------------------------------------------------------
                               Person1-Bank1 process
---------------------------------------------------------------------------------------*/
void P1B3_Process(void)
{
UART2_TX_Str("0P1B3");
while(1)
{
Lcd_Data_Chr(0,0,0,LCD_CLEAR);	
Lcd_Data_Str(1,1,"1.Balance Enqry");
Lcd_Data_Str(2,1,"2.Cash Withdraw");
	
bank_selected=Keypad_Reading();

if((bank_selected=='1'))
{
Lcd_Data_Chr(0,0,0,LCD_CLEAR);	
Lcd_Data_Str(1,1,"Bank-3 Checking");
Lcd_Data_Str(2,1,"Balance........");
Delay(500);
UART2_TX_Str("P1B3B");	
for(count=0;count<5;count++)
{
P1B3_Balance_Amt[count]=UART2_RX_Chr();
}
Lcd_Data_Chr(0,0,0,LCD_CLEAR);
Lcd_Data_Str(1,1,"Bank-3 Balance ");
Lcd_Data_Str(2,12,P1B3_Balance_Amt);
Delay(1000);
Lcd_Data_Str(1,1,"Baln Transaction");
Lcd_Data_Str(2,1,"Completed Thanq ");
Delay(500);
Lcd_Data_Str(1,1,"SCard -F.P Based");
Lcd_Data_Str(2,1,"MultiAcc ATM Crd");
Delay(500);
break;

}
else if((bank_selected=='2'))
{
Lcd_Data_Chr(0,0,0,LCD_CLEAR);	
Lcd_Data_Str(1,1,"Bank-3 Checking");
Lcd_Data_Str(2,1,"For Process....");
Delay(500);
P1B3_Cash_Withdraw();
Lcd_Data_Str(1,1,"WTDL Transaction");
Lcd_Data_Str(2,1,"Completed Thanq ");
Delay(500);
Lcd_Data_Str(1,1,"SCard -F.P Based");
Lcd_Data_Str(2,1,"MultiAcc ATM Crd");
break;
}
else 
{
Lcd_Data_Str(1,1,"In Valid K-Press");
Lcd_Data_Str(2,1,"      Sorry     ");
Delay(350);
}
}	
}

void P1B3_Cash_Withdraw(void)
{
UART2_TX_Str("P1B3W");	

for(count=0;count<5;count++)
{
P1B3_Balance_Amt[count]=UART2_RX_Chr();
}
Lcd_Data_Chr(0,0,0,LCD_CLEAR);
Lcd_Data_Str(1,1,"Bank-3 Balance ");
Lcd_Data_Str(2,12,P1B3_Balance_Amt);
Delay(1300);
d11=(P1B3_Balance_Amt[0]-48);
d22=(P1B3_Balance_Amt[1]-48);
d33=(P1B3_Balance_Amt[2]-48);
d44=(P1B3_Balance_Amt[3]-48);
d55=(P1B3_Balance_Amt[4]-48);

P1B3_Balance_Cash=(d11*10000)+(d22*1000)+(d33*100)+(d44*10)+d55;
P1B3_Enter_Amt();
}


void P1B3_Enter_Amt(void)
{
unsigned int ptr;
ptr=3;
Lcd_Data_Chr(0,0,0,LCD_CLEAR);
Lcd_Data_Str(1,1,"Enter Amount    ");
for(i=0;i<5;i++)
{
P1B3_Withdraw_Amt[i]=Keypad_Reading();
Lcd_Data_Chr(1,2,ptr++,P1B3_Withdraw_Amt[i]);
Delay(250);
}

d11=(P1B3_Withdraw_Amt[0]-48);
d22=(P1B3_Withdraw_Amt[1]-48);
d33=(P1B3_Withdraw_Amt[2]-48);
d44=(P1B3_Withdraw_Amt[3]-48);
d55=(P1B3_Withdraw_Amt[4]-48);

P1B3_Withdraw_Cash=(d11*10000)+(d22*1000)+(d33*100)+(d44*10)+d55;

if(P1B3_Balance_Cash>=P1B3_Withdraw_Cash)
{
Lcd_Data_Str(1,1,"Amount Deducting");
Lcd_Data_Str(2,1,"Please Wait.....");	
P1B3_Balance_Cash=P1B3_Balance_Cash-P1B3_Withdraw_Cash;
Delay(1500);
Lcd_Data_Chr(0,0,0,LCD_CLEAR);	
Lcd_Data_Str(1,1,"Remain Balance  ");	
P1B3_Send_Bal_Cash[0]=(P1B3_Balance_Cash/10000)+'0';	//5
P1B3_Send_Bal_Cash[1]=((P1B3_Balance_Cash%10000)/1000)+'0';//4
P1B3_Send_Bal_Cash[2]=(((P1B3_Balance_Cash%10000)%1000)/100)+'0';//3	
P1B3_Send_Bal_Cash[3]=((((P1B3_Balance_Cash%10000)%1000)%100)/10)+'0';//2
P1B3_Send_Bal_Cash[4]=((((P1B3_Balance_Cash%10000)%1000)%100)%10)+'0';//1
Lcd_Data_Str(2,12,P1B3_Send_Bal_Cash);	
Delay(1500);
UART2_TX_Str (P1B3_Send_Bal_Cash);
}
else
{
Lcd_Data_Str(1,1,"Unable To Process");
Lcd_Data_Str(2,1,"Low Balance      ");
Delay(500);
}
}
/*=====================================================================================*/

