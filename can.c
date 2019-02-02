#include<lpc21xx.h>
#include<prototypes.h>	


 
int Can_Init(void)
{

		PINSEL1|=0x15454000;	/*CAN1 intialization*/
    	C1MOD=1;				/*Reset CAN1 controller*/
    	C1BTR=0x001C001D;		/*Set baud Rate for CAN*/
    	C1MOD=0;				/*Enable CAN1 controller*/

								/*CAN2 intialization*/
    	C2MOD=1;				/*Reset CAN2 controller*/
    	C2BTR=0x001C001D;		/*Set baud Rate for CAN2*/
  		C2MOD=0;				/*Enable CAN2 controller*/
    
	return 0;
}

void SendMessage(unsigned int x)
{
     	while((C2SR&0X00000004)!=0X00000004);	 /// CHECKING BUS IS FREE OR NOT FOR Tx MSG
	
		C2TFI1=0X00040000;		  ///   4 BYTE INFORMATION,DATA LENGTH SET
		C2TDA1=x; 				/*Transmit data bytes 1-4 (1)*/	   //STORE 4-BYTE
		C2TID1=0X045;			// tx id
		C2CMR=0X00000021;
		while((C2GSR& 0X00000008)!=0X00000008);

	 
}


