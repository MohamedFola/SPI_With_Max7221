/*
 * SPI_With_Max7221
 * Author : Mohamed Hassan Hassan
 */ 
#define F_CPU 8000000UL
#include <util/delay.h>
#include "_SPI_Driver_Master.h"

// Command Address
#define Mode_Register_Address          0x09
#define Intensity_Regitser_Address     0x0A
#define Scan_Limit_Register_Address    0x0B
#define Shut_Down_Register_Address     0x0C

// 7-Segment Number
#define Fourth_7_Segment               0x01
#define Third_7_Segment                0x02
#define Second_7_Segment               0x03
#define First_7_Segment                0x04



void MAX7221_Send(unsigned char Command, unsigned char Data)
{
	SET_BIT_LOW(SPI_Port_Name, SS);
	SPI_Master_Send(Command);
	_delay_ms(1);
	SPI_Master_Send(Data);
	SET_BIT_HIGH(SPI_Port_Name, SS);
}

int main(void)
{
	unsigned int Counter = 1890;
    SPI_Init_Master(Clk_Rate_FOSC_divisable_by_16, Data_Order_MSB, Clk_Polarity_IDLE_LOW, Clk_Phase_LEADING);
	MAX7221_Send(Mode_Register_Address,       0xff);          // Enable Decode Mode for digits 7-0
	MAX7221_Send(Intensity_Regitser_Address,  0x09);          // Intensity 10/16
	MAX7221_Send(Scan_Limit_Register_Address, 0x03);          // 4 7-Segments are used
	MAX7221_Send(Shut_Down_Register_Address,  0x01);          // Turn on ship --> Normal Operation
	
	MAX7221_Send(Fourth_7_Segment,  (Counter/1000)%10);
	MAX7221_Send(Third_7_Segment,   (Counter/100)%10);
	MAX7221_Send(Second_7_Segment,  (Counter/10)%10);
	MAX7221_Send(First_7_Segment,   (Counter%10));
	_delay_ms(1000);
	
    while (1) 
    { 
		MAX7221_Send(Fourth_7_Segment,  (Counter/1000)%10);
		MAX7221_Send(Third_7_Segment,   (Counter/100)%10);
		MAX7221_Send(Second_7_Segment,  (Counter/10)%10);
		MAX7221_Send(First_7_Segment,   (Counter%10));
		
		_delay_ms(100);
		(Counter > 9999) ? (Counter = 0) : (Counter++);
	}
}

