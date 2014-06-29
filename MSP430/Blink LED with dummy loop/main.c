#include <msp430.h>
#include <stdint.h>

unsigned int i = 0;

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    P1DIR |= 0x41; // P1DIR is a register that configures the direction of a port pin as an output (1) or an input (0). AKA port 1.1 and 1.6 are now outputs

    P1OUT &= 0x00; // Make sure all registers are set to low before changing anything

    P1OUT |= 0x40; // Set Port 1.6 to output high (turn on green LED)

    while(1){ // infinite loop

    	P1OUT ^= 0x41; // flip the red and green LED on and off

    	for(i=0; i < 65000; i++); // dummy delay
    }
}
