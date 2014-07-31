#include <msp430.h> 

//	Don't think this is working properly...

#define LED0 BIT0
#define LED1 BIT6

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    // Set up pins
    P1OUT = 0;	// Set all pins low
    P1DIR = LED0 + LED1;	// Set LEDs as outputs
    P1REN |= BIT3;
    P1OUT |= BIT3;

    // Set up interrupts on P1.3 (left button)
    P1IE |= BIT3;
    P1IES |= BIT3;
    P1IFG &= ~BIT3;

    //enable global interrupts
    _enable_interrupts();

    while(1);
}

#pragma vector=PORT1_VECTOR
__interrupt void button(void){
	P1OUT ^= LED0; // Toggle LED
	P1IFG &= ~BIT3;
}
