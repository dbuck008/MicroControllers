//***************************************************************************************
//  MSP430 Blink the LED Demo - Software Toggle P1.0
//
//  Description; Toggle P1.0 by xor'ing P1.0 inside of a software loop.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430x5xx
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  J. Stevenson
//  Texas Instruments, Inc
//  July 2011
//  Built with Code Composer Studio v5
//***************************************************************************************

#include <msp430.h>

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer
	P1DIR |= 0x01;					// Set P1.0 to output direction

	// Messing with the speed of the DCO clock source
	DCOCTL &= ~0xE0;	// Clear bits 5-7 of the DCOCTL register
	DCOCTL |= 0xE0; 	// Set bits 5-7 all high making DCOx = 7 (the highest value)
	BCSCTL1 &= ~0x0F;	// Clear bits 0-3 in the BCSCTL1 Register
	BCSCTL1 |= 0x0C;	// Set bits 0-3 all high making RSEL = 0 (the lowest value)

	for(;;) {
		volatile unsigned int i;	// volatile to prevent optimization

		P1OUT ^= 0x01;				// Toggle P1.0 using exclusive-OR

		i = 10000;					// SW Delay
		do i--;
		while(i != 0);
	}
	
	return 0;
}
