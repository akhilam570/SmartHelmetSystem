void Storing_FPs(void)
{
if(serial_data[9]==fp_cnt)//intilaly starts with 1
{
First_Person_flag=1;
FP_No[fpc++]=fp_cnt++;	
}

//for(i=1;i<=fpc;i++)
//{
//Lcd_Data_Chr(1,2,i,FP_No[i]+'0');
//}	

if(FP_No[1]==serial_data[9])    //1
{
Lcd_Data_Str(2,1,"F.P-1           ");
}

if(FP_No[2]==serial_data[9]) 
{
Lcd_Data_Str(2,1,"F.P-2           ");
}

if(FP_No[3]==serial_data[9]) 
{
Lcd_Data_Str(2,1,"F.P-3           ");
}


if(FP_No[4]==serial_data[9]) 
{
Lcd_Data_Str(2,1,"F.P-4           ");
}

if(FP_No[5]==serial_data[9]) 
{
Lcd_Data_Str(2,1,"F.P-5           ");
}

}

/*************************************************************************/
void Enrolling_FPs(unsigned char no_fps)
{
while(1)
{
for(No_FPs=1;No_FPs<=no_fps;)
{
Lcd_Data_Chr(0,0,0,LCD_CLEAR);
Lcd_Data_Str(1,1,"F.P. No:");
Lcd_Data_Chr(1,1,9,No_FPs+48);
//Press_To_Enroll//Press_To_Chk_Erl	
{
Lcd_Data_Str(1,1,"Checking F.P.");
Chk_Enroll_FP();
}
}
if(No_FPs>=no_fps)
{
Lcd_Data_Str(1,1,"2-F.P.s Enrolled");
Lcd_Data_Str(1,1,"Successfully....");
First_Person_flag=Second_Person_flag=0;
Delay(350);
break;
}
}
}

/************************************************************************************
THIS WAS THE COMMAND FORMAT 
************************************************************************************/
/*__________________________________________________________________
_________________________PCAKET_HEADER_______________________________*/
void Packet_Header(void)
{
UART1_TX_Chr(0xEF);
UART1_TX_Chr(0x01);
} 
/*__________________________________________________________________
_________________________CHIP_ADDRESS_______________________________*/
void Chip_Add(void)
{
UART1_TX_Chr(0xFF);
UART1_TX_Chr(0xFF);
}
/*__________________________________________________________________
________________________PACK MARK___________________________________*/

void Pack_mark(void)
{
UART1_TX_Chr(0x01);
}

/*__________________________________________________________________
________________________PACK_LENGTH_________________________________*/

void Pack_Length(unsigned char lsb,unsigned char msb)
{
UART1_TX_Chr(lsb);
UART1_TX_Chr(msb);
}

/*__________________________________________________________________
________________________BUFFER_ID___________________________________*/

void Buffer_ID(unsigned char buff_id)
{
UART1_TX_Chr(buff_id);
}

/*__________________________________________________________________
_________________________COMMAND____________________________________*/
void Fp_cmd(unsigned char cmd)
{
UART1_TX_Chr(cmd);
}
/*__________________________________________________________________
_________________________PAGE_ID____________________________________*/

void Page_Id(unsigned char lsb_id1,unsigned char msb_id1)
{
UART1_TX_Chr(lsb_id1);
UART1_TX_Chr(msb_id1);
}
/*__________________________________________________________________
_________________________CHECKSUM___________________________________*/
void Check_Sum(unsigned char lsb,unsigned char msb)
{
UART1_TX_Chr(lsb);
UART1_TX_Chr(msb);
}
/*************************************************************************
**************************************************************************/
	
void FP_Init(void)	
{
Lcd_Data_Str(2,1,"F.P. Initing.... ");
Verify_Delete_All();
Lcd_Data_Str(2,1,"   F.P. Inited   ");
Delay(800);
}


/**************************************************************************************

ENROLL process: Generate Image-->Generate Character--->Store charater.....

***************************************************************************************/

void Chk_Enroll_FP(void)
{
Verify_Identify_Enroll();
Lcd_Data_Chr(0,0,0,LCD_CLEAR);
Lcd_Data_Str(2,1,"F.P.-Enrolling...");
Enroll_FP();
}

void Enroll_FP(void)
{
Verify_GenImage();
Verify_GenChar();
Verify_StoreChar();
}
}
}

/**************************************************************************************
    Generate Image sequence with verify 
***************************************************************************************/




void Verify_GenImage(void)
{
Packet_Header();
Chip_Add();
Pack_mark();
Fp_cmd(0x01);
if(UART1_RX_Chr()!=0XEF)
if(UART1_RX_Chr()!=0X01)

for(i=0;i<10;i++)
{
serial_data[i]=UART1_RX_Chr();
}

if(serial_data[7]==0x00)
{
Flag_GenImage=1;
}
if(serial_data[7]==0x02)
{
Lcd_Data_Str(1,2,"no finger on sen");
Delay(400);
}

//clear_buffer();
}




/**************************************************************************************
Generate Character for the Generated Image with verify
***************************************************************************************/



void Verify_GenChar(void)
{
Packet_Header();
Chip_Add();
Pack_mark();
Fp_cmd(0x02);
Buffer_ID(0x01);
if(UART1_RX_Chr()!=0X01)
for(i=0;i<10;i++)
{
serial_data[i]=UART1_RX_Chr();
}

if(serial_data[7]==0x00)
{

Flag_GenChar=1;
}

if(serial_data[7]==0x01)
{

Lcd_Data_Str(2,1,"error on receive");
Delay(400);
}

if(serial_data[7]==0x06)
{

Lcd_Data_Str(2,1,"over disprder FP");
Delay(400);
}
if(serial_data[7]==0x07)
{

Lcd_Data_Str(2,1,"lack char/small FP");
Delay(400);
}

if(serial_data[7]==0x15)
{

Lcd_Data_Str(2,1,"invalid prim img");
Delay(400);
}

}

/**************************************************************************************
Store Character for the Generated Image and generated Character with verify
***************************************************************************************/


void Verify_StoreChar(void)
{
Pg_ID=Pg_ID+1;
Packet_Header();
Chip_Add();
Pack_mark();
Fp_cmd(0x06);
Buffer_ID(0x01);


for(i=0;i<10;i++)
{
serial_data[i]=UART1_RX_Chr();
}

if(serial_data[7]==0x00)
{
No_FPs++;	
Lcd_Data_Str(1,1,"storage Success ");
Lcd_Data_Str(2,1," F.P.- Enrolled ");
Delay(400);

}
if(serial_data[7]==0x01)
{
Lcd_Data_Str(2,1,"receive error");
Delay(400);
}

if(serial_data[7]==0x0b)
{
Lcd_Data_Str(2,1,"ID beyond mem");
Delay(400);
}

if(serial_data[7]==0x18)
{
Lcd_Data_Str(2,1,"unable to store");
Delay(400);
}

//clear_buffer();
}

/*************************************************************************************************************
****************************************************************************************************************/

/**************************************************************************************
                         Identify the FP with location
***************************************************************************************/

// You Get The FP Storage Address

void Verify_Identify_Enroll(void)
{
Packet_Header();
Chip_Add();
Pack_mark();
Fp_cmd(0x11);

for(i=0;i<14;i++)
{
serial_data[i]=UART1_RX_Chr();
}

if(serial_data[7]==0x00)
{
Flag_FP_exsist=0;
Lcd_Data_Str(1,1,"   F.P-Exists   ");
Lcd_Data_Str(2,1,"   F.P-I.D:");	//16 BYTE LOCATION(FFFF) (8,9)LOCATIONS AS SHOWING ONLY 9 TH
for(i=9;i<10;i++)
{
x=serial_data[i]/10;
d1=serial_data[i]%10;
d2=x%10;
d3=x/10;
d1=d1+48;
d2=d2+48;
d3=d3+48;

Lcd_Data_Chr(1,2,12,d3);
Lcd_Data_Chr(1,2,13,d2);
Lcd_Data_Chr(1,2,14,d1);
Lcd_Data_Chr(1,2,15,' ');
Delay(300);
}
}

if(serial_data[7]==0x02)
{
Flag_FP_exsist=1;
Lcd_Data_Str(2,1,"no finger on sen");
Delay(400);
}

if(serial_data[7]==0x09)
{
Flag_FP_exsist=1;
Lcd_Data_Str(2,1,"F.P Don't exists");
Delay(400);
}
Storing_FPs();
//clear_buffer();
}




/**************************************************************************************
***************************************************************************************/



/**************************************************************************************
Delete All Finger Prints
***************************************************************************************/




void Verify_Delete_All(void)
{
Packet_Header();
Chip_Add();
Pack_mark();
Pack_Length(0x00,0x03);
Fp_cmd(0x0D);
Check_Sum(0x00,0x11);

for(i=0;i<10;i++)
{
serial_data[i]=UART1_RX_Chr();
}	

if(serial_data[7]==0x00)
{
Lcd_Data_Str(2,1,"   Delete  ok   ");
Delay(400);
}
if(serial_data[7]==0x10)
{
Lcd_Data_Str(2,1,"error in Delete");
Delay(200);
}
if(serial_data[7]==0x11)
{
Lcd_Data_Str(2,1,"unable to delete");
Delay(200);
}

}
 


/*
void clear_buffer(void)
{

for(i=0;i<16;i++)
{
serial_data[i]=0x00;
//n[i]=0x00;
}
}
*/














/*
if(serial_data[0]==0xff)
{
Lcd_Data_Chr(0,0,0,LCD_CLEAR);
Lcd_Data_Str(2,1," chip add:1-ff ");
Delay(200);
}

if(serial_data[1]==0xff)
{
Lcd_Data_Chr(0,0,0,LCD_CLEAR);
Lcd_Data_Str(2,1," chip add:2-ff ");
Delay(200);
}
if(serial_data[2]==0xff)
{
Lcd_Data_Chr(0,0,0,LCD_CLEAR);
Lcd_Data_Str(2,1," chip add:3-ff ");
Delay(200);
}
if(serial_data[3]==0xff)
{
Lcd_Data_Chr(0,0,0,LCD_CLEAR);
Lcd_Data_Str(2,1," chip add:4-ff ");
Delay(200);
}

if(serial_data[4]==0x07)
{
Lcd_Data_Chr(0,0,0,LCD_CLEAR);
Lcd_Data_Str(2,1,"  Pcackge Idfy  ");
Delay(200);
}

if(serial_data[5]==0x00)
{
Lcd_Data_Chr(0,0,0,LCD_CLEAR);
Lcd_Data_Str(2,1,"Pcackge lnth:00 ");
Delay(200);
}

if(serial_data[6]==0x03)
{
Lcd_Data_Chr(0,0,0,LCD_CLEAR);
Lcd_Data_Str(2,1,"Pcackge lnth:03  ");
Delay(200);
}

if(serial_data[7]==0x0d)
{
Lcd_Data_Str(1,1,"ur getting cmd.!@#");
Delay(200);
}

if(serial_data[8]==0x00)
{
Lcd_Data_Str(1,1,"Chk sum:00");
Delay(200);
}

if(serial_data[9]==0x11)
{
Lcd_Data_Str(1,1,"Chk sum:55");
Delay(200);
}
*/





