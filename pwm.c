#include<LPC21XX.H>
#include<prototypes.h>
void PWM_INIT()
{
	PWMPR  = 0x00000020;	//Load prescaler
	PWMPCR = 0x00002424;		//PWM channel 2 and channel 5 double edge control, output enabled
	PWMMCR = 0x00000002;	//On match0 with timer reset the counter
	PWMMR0 = 0x00003A98;	//set cycle rate to sixteen ticks
	PWMMR1 = 0x00000010;	//set rising edge of SELECT_PWM2 to 2 ticks
	PWMMR2 = 0x00000800;		//set falling edge of SELECT_PWM2 to 8 ticks 3A98/2
	PWMMR5 = 0x00000800;
	PWMTCR = 0x00000009;	//enable counter and PWM, release counter from reset
}


void delay1(unsigned int t)
{
	int i,j;
	for(i=0;i<100;i++)
	for(j=0;j<t;j++);
}

void DC_MOTOR_CNT(char SPEED)
{	
	//IOCLR1 = 0x00200000;
	if(SPEED==0)		 
	{
		PINSEL0 = 0x00000005; // UART0 TX-RX  and SELECT_PWM2 OFF
		IOCLR0 |= 0x00000080; // making P0.7 as 0	
			delay1(10);
		   	PWMPCR = 0x0000000  ;
								
	}//Motor OFF
	
	if(SPEED==1)//Speed 1
	{
		PINSEL0|=0X8000;			
		IOCLR0|= 0x00000000;
		
		PWMPCR = 0x0002424;
		
			PWMMR2 = 0x00002500;

			PWMLER = 0x00000026;
			 
			//LCD_DATA_WR("SPEED 1 ");
		/// FG_Delay();
			delay1(10);	
	}//end of speed 1
	if(SPEED==2)//Speed 2
	{							 
		
		
		
		PINSEL0|=0X8000;
		PWMPCR = 0x0002424;
	
			PWMMR2 = 0x00001000;//PWMMR2 = 0x0000300;
			PWMLER = 0x00000026; 
			delay1(10);
	}//end of speed 2

	if(SPEED==3)//Speed 3		
	{
	/*	PINSEL0|=0X0000;
		IODIR0|=0X00000080;
		IOSET0|=0X00000080;*/
	
	
	
	
		PINSEL0|=0X8000;
	
		PWMPCR = 0x0000404;  
		PWMPCR = 0x0002424;
			PWMMR2 = 0x00000100;;
			PWMLER = 0x00000026;
			delay1(10);
					 		
	}//end of speed 3
  
}//end of DC_MOTOR_CNT
//}

