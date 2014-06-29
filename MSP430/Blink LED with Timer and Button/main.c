#include "msp430g2553.h"

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD;	// Stop WDT
	TACCTL0 = CCIE;	// CCR0 interrupt enabled
	TACTL = TASSEL_2 + MC_1 + ID_3;	// SMCLK/8, upmode
	CCR0 =  10000;	// 12.5 Hz
	P1DIR |= BIT0 + BIT6;	// P1.0 and P1.6 pins output, the rest are input
	P1OUT &= 0x00;	// Shut. Down. Everything... :)
	P1IE |= BIT3;	// P1.3 interrupt enabled
	P1IES |= BIT3;	// P1.3 Hi/lo edge
	P1IFG &= ~BIT3;	// P1.3 IFG cleared
	_BIS_SR(CPUOFF + GIE);	// Enter LPM0 w/ interrupt
	while(1){};	//Loop forever, we work with interrupts!
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
   P1OUT ^= BIT0;                          // Toggle P1.0
}
// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
   P1OUT ^= BIT6;                          // Toggle P1.6
   P1IFG &= ~BIT3;                     // P1.3 IFG cleared
}
