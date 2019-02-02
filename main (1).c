#include<LPC21xx.h>
#include<prototypes.h>


unsigned int  MSG[4];
unsigned char BYTE[3],tick;
unsigned int D;	

void ULTRA_S()
{
	unsigned char i, flag=0, dist[3]={'\0'};
//again:
	D=0;
	while(UART1_RECV()!='R');
	
	for(i=0; i<3; i++)
	{	dist[i]=UART1_RECV();	}
	
	for(i=0; i<3; i++)
	{	
		if( flag==0 && dist[i] !='R' )	
			{
				if( dist[i]>= '0'&& dist[i]<= '9' )
				{
					BYTE[i]=dist[i];
				
					D*=10;
					D+=(BYTE[i]-0x30);
				}	
			}

		else
			{	
				BYTE[i]='\0';
				flag=1;
			}
	}
		  
	LCD_CMD(0x01);
	LCD_STRING("DIST: ");
//	LCDCMD(0xC4);
	LCD_STRING(BYTE);
	LCD_STRING(" CMS ");
	Delay(2000);
	if ( D==0 )
	{}
	else if( D>0 && D <= 20 )
	{

	    IODIR1 |=0x00070000;
		IOSET1 |=0x00040000;
	    DC_MOTOR_CNT(1);
		LCD_CMD(0x01);
		LCD_STRING("OBSTACLE VERY ");
		LCD_CMD(0xC0);
		LCD_STRING("NEAR GO SLOW  ");
		Delay(2500);
         UART0_TX_ST("AT+CMGS=\"9731204017\"");
		 UART0_TX(0X0A);
	     UART0_TX(0X0D);
         UART0_TX_ST("OSTACLE DISTANCE IS VERY LESS, VEHICLE MOVING SLOWLY");
	   	 UART0_TX(0x1A);	
 		Delay(5000); 
	}

	else if( D>20 && D<35 )
	{ 
	    IODIR1 |=0x00070000;
	   IOCLR1 |=0x00040000;
	   DC_MOTOR_CNT(2);	
		LCD_CMD(0x01);
		LCD_STRING(" OBSTACLE AHEAD ");
		LCD_CMD(0xC0);
		LCD_STRING("     GO NORMAL    ");	
		Delay(2500);
	}

	else if( D>=35 && D<300 )
	{
		IODIR1 |=0x00070000;
	   IOCLR1 |=0x00040000;
		DC_MOTOR_CNT(3);
		LCD_CMD(0x01);
		LCD_STRING("NO OBSTACLE");
		Delay(2500);
	}

}
void ir_Check4()
 {
	unsigned int IR;

  IODIR0 &=0xFFFBFFEF;  ////p0.18 for ir   /// p0.4 for ir1
  LCD_INIT();
IR=IOPIN0;
IR=IR & 0x00040010;
  if(IR==0X00040010)	  ////p0.18 for ir
		{

		SendMessage(3);
         ReceiveMessage(); 
		    
		}
	else if(IR==0X00000010)	  ////p0.04 for ir
		{
		SendMessage(1);
         ReceiveMessage(); 
		    
		}
	else if(IR==0X00040000)	  ////p0.18 for ir
		{

		SendMessage(2);
         ReceiveMessage();     
		}
	else
		{  
		    IODIR1 |=0x00030000;
			IOCLR1 |=0x00030000;
		    LCD_CMD(0x01);
		 	LCD_STRING("   LANE IS  NOT   ");
			LCD_CMD(0xc0);
			LCD_STRING("    DETECTED   ");
			Delay(2500);
		}

	
 } 

 int ReceiveMessage (void)
  {
    	while((C1SR&0X01));

		MSG[0]=C1RID;	 		//The 11-bit Identifier field of the current received message. 
		MSG[1]=C1RDA;   		// FIRST BYTE OF DATA
		MSG[2]=C1RDB;	 		//SECOND  BYTE OF DATA
		MSG[3]=C1RFS;	   	
		C1CMR=0X00000004;  
		
		if(MSG[1] == 1)
	 	{ 
	    	IODIR1 |=0x00030000;
			IOSET1 |=0x00010000;
			IOCLR1 |=0x00060000;
	 	    LCD_CMD(0x01);
		 	LCD_STRING("   LEFT LANE   ");
			LCD_CMD(0xc0);
			LCD_STRING("    DETECTED   ");
			Delay(2500);
			
			UART0_TX_ST("AT+CMGS=\"7411277626\"");
		 UART0_TX(0X0A);
	        UART0_TX(0X0D);
           UART0_TX_ST("LEFT LANE DETECTED ");
		UART0_TX(0x1A);	
 		Delay(5000);
     	}
    	
		else if (MSG[1] == 2) 
		{
		    IODIR1 |=0x00030000;
			IOSET1 |=0x00020000;
			IOCLR1 |=0x00050000;
	 	  LCD_CMD(0x01);
		 	LCD_STRING("   RIGHT LANE   ");
			LCD_CMD(0xc0);
			LCD_STRING("    DETECTED   ");
			Delay(2500);

			UART0_TX_ST("AT+CMGS=\"9731204017\"");
		 UART0_TX(0X0A);
	        UART0_TX(0X0D);
         UART0_TX_ST("RIGHT LANE DETECTED");
		UART0_TX(0x1A);	
 		Delay(5000); 

    	}
	 	
		else if (MSG[1] == 3) 
		{
		    IODIR1 |=0x00070000;
			IOSET1 |=0x00070000;
	     ///	IOSET1 |=0x00040000;
			DC_MOTOR_CNT(1);
	   	    LCD_CMD(0x01);
		 	LCD_STRING("  BOTH SIDES   ");
			LCD_CMD(0xc0);
			LCD_STRING("    DETECTED   ");
			Delay(2500);
   

			UART0_TX_ST("AT+CMGS=\"9731204017\"");
		 UART0_TX(0X0A);
	        UART0_TX(0X0D);
          UART0_TX_ST("BOTH LANE DETECTED VEHICLE SLOWED");
		UART0_TX(0x1A);	
 		Delay(5000); 
		} 

    	else
    		return 1;

   return 0;
} 

void main()
{
 IODIR1 |=0x00070000;
  LCD_INIT();
  LCD_CMD(0x01);
  LCD_CMD(0x80);
  LCD_STRING("LCD INIT...."); 
   Delay(2000);

 UART0_INIT();
 LCD_CMD(0x01);
 LCD_CMD(0x80);
 LCD_STRING("UART0 INIT.... "); 
  Delay(2000);

 UART1_INIT();
 LCD_CMD(0x01);
 LCD_CMD(0x80);
 LCD_STRING("UART1 INIT.... "); 
  Delay(2000);
 
  Can_Init() ;
 LCD_CMD(0x01);
 LCD_CMD(0x80);
 LCD_STRING("CAN INIT.... ");
  Delay(2000);

 GSM_INIT()	;
 LCD_CMD(0x01);
 LCD_CMD(0x80);
 LCD_STRING("GSM INIT.... ");
  Delay(2000); 
  
  PWM_INIT();
  LCD_CMD(0x01);
 LCD_CMD(0x80);
 LCD_STRING("PWM INIT.... ");
  Delay(2000); 	
  DC_MOTOR_CNT(3);	

 while(1)
{
   ir_Check4();
   ULTRA_S();
  ULTRA_S();ULTRA_S();	ULTRA_S();
     
	 
	
		  
 
 }
 
 }
