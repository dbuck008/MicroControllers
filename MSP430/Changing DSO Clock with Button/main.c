#include <msp430G2553.h>

#define LED0 BIT0

void blinkLED();

char x;
unsigned int i;
unsigned int delay = 60000;

void main(void){
	WDTCTL = WDTPW + WDTHOLD;	// Stop the watchdog timer
	
	// setup
	P1OUT = 0;
	P1DIR = LED0;
    P1REN |= BIT3;
    P1OUT |= BIT3;

	while(1){
		// Setup DSO(7,3)
		BCSCTL1 &= ~0x0F;
		BCSCTL1 |= 0x07;
		DCOCTL &= ~0xE0;
		DCOCTL |= 0x60;

		blinkLED();

		while((P1IN & BIT3) == BIT3);

		// Setup DSO(9,5)
		BCSCTL1 &= ~0x0F;
		BCSCTL1 |= 0x09;
		DCOCTL &= ~0xE0;
		DCOCTL |= 0xA0;

		blinkLED();

		while((P1IN & BIT3) == BIT3);

		// Setup DSO(2,6)
		BCSCTL1 &= ~0x0F;
		BCSCTL1 |= 0x02;
		DCOCTL &= ~0xE0;
		DCOCTL |= 0xC0;

		blinkLED();

		while((P1IN & BIT3) == BIT3);


	}
}

void blinkLED(){
	for(x=0; x<10; x++){
		P1OUT ^= LED0;
		for(i=0; i<delay; i++);
	}
}
