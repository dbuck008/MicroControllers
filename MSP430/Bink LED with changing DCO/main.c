#include <msp430.h> 

#define LED0	BIT0
#define LED1	BIT6

unsigned int i;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    P1DIR = 0x01;
    P1OUT |= 0x01;

    TACTL = TASSEL_2 + ID_3 + MC_1 + TAIE;
    TACCR0 = 0xFFFF;

    // Calibrating DCO and BCS using calibration constants (1, 8, 12, and 16 MHz)
    DCOCTL = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;

    _BIS_SR(GIE); // Enable global interrupts

    while(1);
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void timerA0_ISR(void){
	P1OUT ^= 0x01;	// Toggle output
	TACTL &= ~0x01;	// Clear interrupt flag in TACTL
}
