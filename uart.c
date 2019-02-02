#include <LPC21xx.H>
#include<prototypes.h>

void UART0_INIT()
{
	PINSEL0|=0X000000005;	
	U0LCR=0X83;			 
	U0DLL=0X61;
	U0DLM=0X00;
	U0LCR=0X03;
}

void UART0_TX(unsigned char rec)
{
   	U0THR=rec;
	while(!(U0LSR&0X20));
}

unsigned char UART0_RECV()
{
	unsigned char a;

	while(!(U0LSR&0X01));
	a=U0RBR;
	return(a);
}

void UART0_TX_ST(unsigned char *Ptr)
{
	while(*Ptr)
	{
	UART0_TX(*Ptr);
	Ptr++;
	}
}

void UART1_INIT()
{
	PINSEL0|=0X00050000;	
	U1LCR=0X83;			 
	U1DLL=0X61;
	U1DLM=0X00;
	U1LCR=0X03;
}

void UART1_TX(unsigned char rec)
{
   	U1THR=rec;
	while(!(U1LSR&0X20));
}

unsigned char UART1_RECV()
{
	unsigned char a;

	while(!(U1LSR&0X01));
	a=U1RBR;
	return(a);
}

void UART1_TX_ST(unsigned char *Ptr)
{
	while(*Ptr)
	{
	UART1_TX(*Ptr);
	Ptr++;
	}
}
