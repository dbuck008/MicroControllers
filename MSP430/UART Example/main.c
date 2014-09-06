#include <msp430.h> 

/*
 * UART Example
 * Dillon Buck
 * 6/19/2014
 */

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    // Select primary peripheral on pins 1.1 and 1.2 so UART is enabled
    P1SEL |= BIT1 + BIT2;
    P1SEL2 |= BIT1 + BIT2;

    // Set up Baud rate. This can be done with the slow crystal (32.768kHz)
    // if installed or the fast DCO or external crystal
    DCOCTL = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;

    // Reset the UCA0 to configure USCI
    UCA0CTL1 = UCSWRST;

    // Configure UART
    UCA0CTL1 = UCSSEL_2;
    UCA0BR0 = 104;
    UCA0MCTL = UCBRS_1;

    // Take USCI out of reset mode
    UCA0CTL1 &= ~UCSWRST;

    // Enable RX interrupt
    IE2 = 1;

    // Enable global interrupts
    _BIS_SR(LPM0 + GIE);

}

// Echo back the RXed character
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI_RX_ISR(void){
	while(!(IFG2&UCA0TXIFG));	// USCI_A0 TX buffer read
	UCA0TXBUF = UCA0RXBUF;		// TX -> RXed character
}
