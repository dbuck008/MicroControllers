#include <msp430.h>

#define LED0	BIT0
#define LED1	BIT6

unsigned int value = 0;

void configADC();

void main(void) {
	// Set up clocks
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	BCSCTL1 = CALBC1_1MHZ;	// Set the Basic Clock System Control 1 to a 1 MHz clock
	DCOCTL = CALDCO_1MHZ;	// Set the Digital Control Oscillator  to a 1 MHz clock
	BCSCTL2 &= ~(DIVS_3);	// Set the SMCLK divider to 8

	// Set up LEDs
    P1DIR = 0x0041; //P1DIR |= LED0 + LED1;  // Set pin 1.4 to Input (0) and pin 1.1/l.6 (LED0 and LED1) to output (1)
    P1SEL |= BIT5;	// Set the input pin for the ADC module
    P1OUT &= ~(LED0 + LED1); // Set pin 1.1 and 1.5 output low

    // Configure the ADC...
    configADC();

    //enable global interrupts
    _enable_interrupt();

    while(1){
    	_delay_cycles(1000);	// Allow ADC to sample and hold
    	ADC10CTL0 |= 0x0002; 	// Set the ENC Bit to 1 to allow for calculation to occur
    	ADC10CTL0 |= 0x0001;	// Start the conversion (This can bet set in the same instruction as the ENC bit and is reset automatically)
    	_bis_SR_register(CPUOFF + GIE);	// Enter low power mode while still keeping interrupts enabled. This lets us enter LPM0 disabling MCLK. Not required to run program, just saves battery
    	value = ADC10MEM;	// The ADC stored the sampled value into the ADC10MEM register (the last 10 bits)

    	if(value < 512){	// Because the ADC is 10 bit, the max value is 1023, 512 is ~half of that
    		// Turn off LED0 and turn on  LED1
    		P1OUT &= ~(LED0 + LED1);
    		P1OUT |= LED1;
    	}else{
    		// Turn off LED1 and turn on LED0
    		P1OUT &= ~(LED0 + LED1);
    		P1OUT |= LED0;
    	}
    }
}

void configADC(void){
	/* Configure ADC  Channel */
	ADC10CTL0 &= ~0x0002; // Set ENC bit to 0 which allows for the other bits to change state
	ADC10CTL1 = 0x5060; //ADC10CTL1 = INCH_5 + ADC10DIV_3;
	ADC10CTL0 = 0x181D; // ADC10CTL0 = SREF_0 + ADC10SHT_3 + ADC10ON + ADC10IE;
	ADC10AE0 = 0x20; // ADC10AEO |= BIT5;
}

//ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void){
	_bic_SR_register_on_exit(CPUOFF);	// Return to active mode
}
