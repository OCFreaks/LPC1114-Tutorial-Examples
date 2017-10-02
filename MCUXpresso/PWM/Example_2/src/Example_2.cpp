/*(C) Umang Gajera - www.ocfreaks.com
http://www.ocfreaks.com/lpc1114-pwm-programming-tutorial/
LPC1114 PWM Tutorial Example 2 - Simple Servo Control.
License: GPL.
More Embedded tutorials @ http://www.ocfreaks.com/cat/embedded/
*/

#include <lpc11xx.h>

#define PRESCALE_US (48-1) //Used by PWM
#define PRESCALE_MS (48000-1) //Used by 16Bit-TMR0 for generating delay
#define PWM_PERIOD 20000 //in micro-seconds

void init32BTMR0_PWM(void);
inline void updatePulseWidth(unsigned int pulseWidth);
void delayMS(unsigned int milliseconds);
void init16BTMR0(void);

int main (void)
{
	//SystemInit(); //called by Startup Code before main(), hence no need to call again.
	LPC_IOCON->PIO1_6 |= 0x2; //Select CT32B0_MAT0 (MAT0.0) function for PWM O/P, Marked as RXD on LPCXpresso Board

	int pulseWidths[] = {
			PWM_PERIOD-1000,PWM_PERIOD-1250,
			PWM_PERIOD-1500,PWM_PERIOD-1750,
			PWM_PERIOD-2000}; //Inverted Pulse Widths
	//Note: PWM_PERIOD-1000 will generate a Right aligned Pulse of 1000us and so on..
	//PWM Pulses in LPC1114 are Right-Aligned or "inverted"!
	const int numPulseWidths = 5;
	int count=1;
	int dir=0; //direction, 0 = Increasing, 1 = Decreasing

	init32BTMR0_PWM(); //Initialize 32Bit-TMR0 as PWM
	init16BTMR0(); //Used by delayMS()

	while(1)
	{
		updatePulseWidth(pulseWidths[count]); //Update LED Pulse Width
		delayMS(1000);

		if(count == (numPulseWidths-1) || count == 0)
		{
			dir = !dir; //Toggle direction if we have reached count limit
		}

		if(dir) count--;
		else count++;
	}
  //return 0; //normally this won't execute ever
}

void init32BTMR0_PWM(void)
{
	/*Assuming CCLK (System Clock) = 48Mhz (set by startup code)*/
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9); //Enable 32Bit-TMR0 Clock
	LPC_TMR32B0->CTCR = 0x0;
	LPC_TMR32B0->PR = PRESCALE_US; //Increment TC at every 47999+1 clock cycles
	//48000 clock cycles @48Mhz = 1 mS
	LPC_TMR32B0->MR3 = PWM_PERIOD; //20ms Period duration
	LPC_TMR32B0->MR0 = PWM_PERIOD-1250; //Default TOFF time in mS
	LPC_TMR32B0->MCR = (1<<10); //Reset on MR3 Match

	LPC_TMR32B0->PWMC = 0x1; //Enable PWM Mode for MAT0.0

	LPC_TMR32B0->TCR = 0x02; //Reset Timer
	LPC_TMR32B0->TCR = 0x01; //Enable timer
}

inline void updatePulseWidth(unsigned int pulseWidth)
{
	LPC_TMR32B0->MR0 = pulseWidth; //Update MR1 with new value
}

void delayMS(unsigned int milliseconds) //Using 16B-TMR0
{
	LPC_TMR16B0->TCR = 0x02; //Reset Timer
	LPC_TMR16B0->TCR = 0x01; //Enable timer

	while(LPC_TMR16B0->TC < milliseconds); //wait until timer counter reaches the desired delay

	LPC_TMR16B0->TCR = 0x00; //Disable timer
}

void init16BTMR0(void)
{
	/*Assuming CCLK (System Clock) = 48Mhz (set by startup code)*/
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7); //Enable 16Bit-TMR0 Clock
	LPC_TMR16B0->CTCR = 0x0;
	LPC_TMR16B0->PR = PRESCALE_MS; //Increment TC at every 47999+1 clock cycles
	//48000 clock cycles @48Mhz = 1 mS
	LPC_TMR16B0->TCR = 0x02; //Reset Timer
}
