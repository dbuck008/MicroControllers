#include <msp430.h> 
#include <msp430g2553.h>

/*
 * main.c
 * Dillon Buck
 * 5/12/2014
 *
 */
void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
	P1DIR = 0x41; // Set port 1.0 and 1.6 to outputs

	P1OUT = 0x48; // Set output pin 1.6 to high (Turn on green LED) AND set port1 pin3 to high output

	P1REN |= 0x08; // Enable pulldown resistor on port1 pin3

	_BIS_SR(GIE); // Enable global interrupts

	P1IE |= 0x08; // enable port1 pin5 interrupts

	P1IES |= 0x08; // Throw flag on high-to-low transition

	// P1IFG |= 0x08; // Used to test interrupt - works (jumps into ISR)

	while(1); // Infinite loop
}

#pragma vector = PORT1_VECTOR
__interrupt void Port_1 (void){
	P1OUT ^= 0x41; // Toggle the LEDs on Push Button
	P1IFG &= ~(0x08);
}
