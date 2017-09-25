/*(C) Umang Gajera - http://www.ocfreaks.com 2011-17.
http://www.ocfreaks.com/lpc1114-timer-programming-tutorial/
LPC1114 Timer example 2.

More Embedded tutorials @ http://www.ocfreaks.com/cat/embedded/
*/
#include <LPC11xx.h>

#define PRESCALE (48000-1) //48000 PCLK clock cycles to increment TC by 1

void initTimer0(void);

int main (void)
{
	//SystemInit(); //called by Startup Code before main(), hence no need to call again.

	LPC_IOCON->PIO1_6 |= 0x2; //Select CT32B0_MAT0 (MAT0.0) function - Marked as TXD on LPCXpresso Board
	LPC_IOCON->PIO1_7 |= 0x2; //Select CT32B0_MAT1 (MAT0.1) function - Marked as RXD on LPCXpresso Board

	initTimer0(); //Initialize Timer0

	while(1)
	{
		//Idle loop
	}
	//return 0; //normally this won't execute
}

void initTimer0(void)
{
	/*Assuming CCLK (System Clock) = 48Mhz (set by startup code)*/
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9); //Enable 32Bit Timer0 Clock
	LPC_TMR32B0->CTCR = 0x0;
	LPC_TMR32B0->PR = PRESCALE; //Increment LPC_TMR32B0->TC at every 47999+1 clock cycles
	//48000 clock cycles @48Mhz = 1 mS

	LPC_TMR32B0->MR0 = 500; //toggle time in mS
	LPC_TMR32B0->MCR = (1<<1); //Reset on MR0 Match
	LPC_TMR32B0->EMR |= (1<<7) | (1<<6) | (1<<5) | (1<<4); //Toggle Match output for MAT0.0(P2.5), MAT0.1(P2.6)

	LPC_TMR32B0->TCR = 0x02; //Reset Timer
	LPC_TMR32B0->TCR = 0x01; //Enable timer
}
