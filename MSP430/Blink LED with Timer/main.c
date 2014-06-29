#include <msp430g2553.h>
/**
 * Main
 * Dillon Buck
 * 5/11/2014
 *
 */
int timerCount;

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    P1DIR = 0x41; // Set port 1.0 and 1.6 to outputs

    P1OUT = 0x40; // Set output port 1.6 to high (turn on green LED)

    TACTL = 0x0222; // enable timer A with SMCLK and continuous timing with interrupts and clear clock

    _BIS_SR(GIE);                 // Enable Global interrupts

    while(1); // Infinite loop
}

// Timer A1 interrupt service routine (NOT CC ISR)
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A (void)
{
	timerCount = timerCount + 1 % 8;
	if (timerCount == 0)
		P1OUT ^= 0x41;
}
