#include <msp430.h> 
#define TXLED	BIT0
#define RXLED	BIT6
#define TXD		BIT2
#define RXD		BIT1

const char string[] = {"Hello World\r\n" };

unsigned int i;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    DCOCTL = 0;	// Lowest DCOx and MODx setting
    BCSCTL1 = CALBC1_1MHZ;	// Set DCO
    DCOCTL = CALDCO_1MHZ;

    P2DIR - 0xFF;	// Set all P2.x pins as outputs
    P2OUT &= 0;		// Set all P2.x pins low
    P1SEL |= RXD + TXD;	// P1.1 = RXD, P1.2 = TXD
    P1SEL2 |= RXD + TXD;
    P1DIR |= RXLED + TXLED;	// Set P1.0 and P1.6 to outputs
    P1OUT &= 0;	// Set all P1.x pins low

	UCA0CTL1 |= UCSSEL_2;	// SMCLK
	UCA0BR0 = 0x08;			// 1MHz 115200
	UCA0BR1 = 0x00;			// 1MHz 115200
	UCA0MCTL = UCBRS_5;		// Modulation UCBRSx = 5
	UCA0CTL1 &= ~UCSWRST;	// Initialize USCI state machine
	UC0IE |= UCA0RXIE;	// Enable USCI_A0 RX interrupt
	
	_bis_SR_register(CPUOFF + GIE);
	while(1);
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void){
	P1OUT |= RXLED;	// Set RX LED on
	if(UCA0RXBUF == 'a'){	// if an 'a' is recieved, reset counter and enable the transmitter interrupt
		i = 0;
		UC0IE |= UCA0TXIE;	// Enable USCI_A0 TX interrupt
		UCA0TXBUF = string[i++];
	}
	P1OUT &= ~RXLED;	// Turn off RX LED
}

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void){
	P1OUT |= TXLED;	// Turn on TX LED
	UCA0TXBUF = string[i++];	// TX next character
	if(i == sizeof string -1){ 	// if TX is over the max size
		UC0IE &= ~UCA0TXIE;	// Disable USCI_A0 TX interrupt
	}
	P1OUT &= ~TXLED;
}
