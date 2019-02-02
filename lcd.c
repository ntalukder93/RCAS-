#include<lpc21xx.h>
#include<prototypes.h>

void LCD_INIT()
{
	unsigned char i,cmd[6]={0x02,0x28,0x08,0x0E,0x06,0x01}; 
    IODIR0 |=0X00003C00;
	IODIR1 |=0X03000000;
	for(i=0;i<6;i++)
	{
		LCD_CMD(cmd[i]);
		delay(50000);
	}
}

void LCD_CMD(unsigned int command)
{
	unsigned int x;
  	x=command;
  	x=x & 0xf0;
  	x=x<<6;
  	IOCLR0 = 0x00003C00;
  	IOSET0=x;
  	IOCLR1=0x03000000;		//register select and enable
  	IOSET1=0x02000000;		//rs=0 n en=1 pin 22 rs
  	delay(50000);
  	IOCLR1=0x02000000;
  	delay(50000);
  	
	x=command;
  	x=x & 0x0f;
  	IOCLR0 = 0x00003C00;
  	x=x<<10;
  	IOSET0=x;
  	IOCLR1=0x03000000;		//register select and enable
  	IOSET1=0x02000000;
  	delay(50000);
  	IOCLR1=0x02000000;
  	delay(50000);
}

void LCD_DATA(unsigned int data)
{
  	unsigned int value;
  	value=data;
  
  	value=value & 0xf0;
  
  	value=value<<6;
  	IOCLR0 = 0x00003C00;
  	IOSET0=value;
  	IOCLR1=0x03000000;
  	IOSET1=0x03000000;
  	delay(50000);
  	IOCLR1=0x02000000;
  	delay(50000);
  
  	value=data;
  	value=value & 0x0f;
  	IOCLR0 = 0x00003C00;
  	value=value<<10;
  	IOSET0=value;
  	IOCLR1=0x03000000;
  	IOSET1=0x03000000;
  	delay(50000);
  	IOCLR1=0x02000000;
  	delay(50000);
}


void delay(unsigned int t)
{
  	unsigned int i;
  	for(i=0;i<=t;i++);
}

void Delay(unsigned int k)
{
	unsigned int i,j;
	for(i=0;i<k;i++)
	for(j=0;j<2000;j++);
}

void LCD_STRING(unsigned char *Ptr)
{
  	while(*Ptr)
  	{
  		LCD_DATA(*Ptr);
  		Ptr++;
  	}
}
