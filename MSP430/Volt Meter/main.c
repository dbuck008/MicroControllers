#include <msp430G2553.h>

float voltage = 0.0;

void ADC_init();

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
	P1OUT = 0;

	ADC_init();

	for(;;){
		ADC10CTL0 |= ENC + ADC10SC;
		while(ADC10CTL1 & ADC10BUSY == 1); // wait until the conversion is over
		voltage = ADC10MEM * 0.0032258;
	}
}

void ADC_init(){
	ADC10CTL0 |= SREF_0 + ADC10SHT_2 + ADC10ON;
	ADC10CTL1 |= INCH_1 + SHS_0;
	ADC10AE0 |= BIT1;
}
