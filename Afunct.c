#include <msp430g2553.h>
#include "Afunct.h"

#define move		500000
#define delay		1500000
#define halfturn	500000
#define fullturn	750000

int32	packet;
int16	packetData[48];
int8	newIRPacket = FALSE;
int8	packetIndex = 0;

void main(void) {

	initMSP430();

	moveForward();

	  P1DIR &= ~BIT3;
	  P1REN |= BIT3;

	    // Left
	    P2DIR |= BIT0;	// 1,2EN as OUT
	    P2DIR |= BIT1;  // Sets direction of left motor
	    P2DIR |= BIT2;							// P2.2 is associated with TA1CCR
	    P2SEL |= BIT2;							// P2.2 is associated with TA1CCTL1

		// Right
	   	P2DIR |= BIT5;  // 3,4EN as OUT
	   	P2DIR |= BIT3;  // direction of right motor
	   	P2DIR |= BIT4;							// P2.2 is associated with TA1CCR2
	   	P2SEL |= BIT4;							// P2.2 is associated with TA1CCTL2

	TA1CTL = ID_3 | TASSEL_2 | MC_1;			// Use 1:8 presclar off MCLK
	TA1CCR0 = 100;								// set signal period

	TA1CCR1 = 50;
	TA1CCTL1 = OUTMOD_7;						// set TACCTL1 to Reset / Set mode

	TA1CCR2 = 50;
	TA1CCTL2 = OUTMOD_3;						// set TACCTL2 to Set / Reset mode

	while(1)  {

		//This runs if we get a new packet from the remote and decodes it to control the code
		if(newIRPacket){

			_disable_interrupt();

			if(packet == VOL_UP){
				moveForward();
			}else if(packet == VOL_DW){
				moveBackward();
			}else if(packet == TWO ){
				rotateLeft();
				__delay_cycles(fullturn);
			}else if(packet == ONE){
				rotateRight();
				__delay_cycles(fullturn);
			}else{
				stopMoving();
			}

			//Now we reset the interrupt so we can run through this cycle again.
			_enable_interrupt();

			initMSP430();
			newIRPacket= FALSE;
		}


	}
}

// -----------------------------------------------------------------------
//
// The purpose of this code is to decode the IR packets. This configures the MSP 430
// to allow it to have interrupts on positive edges and as a result work off of a
// time/clock cycle. The P2.6 pin has an ISR which serves to switch the sensitivity
// of the interrupt and in effect measure the times of the high/low pulses coming
// from the decoder.
//
// -----------------------------------------------------------------------

void initMSP430() {

	IFG1=0; 							// clear interrupt flag1
	WDTCTL=WDTPW+WDTHOLD; 				// stop Watchdog timer
	BCSCTL1 = CALBC1_8MHZ;
	DCOCTL = CALDCO_8MHZ;

	P2SEL  &= ~BIT6;					// Setup P2.6 as GPIO
	P2SEL2 &= ~BIT6;
	P2DIR &= ~BIT6;
	P2IFG &= ~BIT6;
	P2IE  |= BIT6;

	HIGH_2_LOW;
	TA0CCR0 = 0xFFFF;					// This serves to create a 16mS roll-over
	TACTL &= ~TAIFG;					// Just to clear the flag before we start interrupts and such
	TACTL = ID_3 | TASSEL_2 | MC_1;

	_enable_interrupt();
}

void moveForward(){

	//For the Left
	P2OUT |= BIT0;
	P2OUT &= ~BIT1;
	TA1CCTL1 = OUTMOD_3;

	//For the Right
	P2OUT |= BIT5;
	P2OUT |= BIT3;
	TA1CCTL2 = OUTMOD_7;
}

void moveBackward(){

	//For the Left
	P2OUT |= BIT0;
	P2OUT |= BIT1;
	TA1CCTL1 = OUTMOD_7;

	//For the Right
	P2OUT |= BIT5;
	P2OUT &= ~BIT3;
	TA1CCTL2 = OUTMOD_3;
}

void stopMoving(){

	P2OUT &= ~BIT0;
	P2OUT &= ~BIT5;
}

void rotateLeft(){
	//For the Left
	P2OUT |= BIT0;
	P2OUT &= ~BIT1;
	TA1CCTL1 = OUTMOD_3;

	// For the Right
	P2OUT |= BIT5;
	P2OUT &= ~BIT3;
	TA1CCTL2 = OUTMOD_3;
}

void rotateRight(){

	//For the Left
	P2OUT |= BIT0;
	P2OUT |= BIT1;
	TA1CCTL1 = OUTMOD_7;

	//For the Right
	P2OUT |= BIT5;
	P2OUT |= BIT3;
	TA1CCTL2 = OUTMOD_7;
}

// -----------------------------------------------------------------------
//
// We want an interrupt to happen whenever we get a positive or negative edge
// to account for whenever a pin changes.
//
// -----------------------------------------------------------------------


#pragma vector = PORT2_VECTOR			// This is from the MSP430G2553.h file

__interrupt void pinChange (void) {

	int8	pin;
	int16	pulseDuration;

	if (IR_PIN)		pin=1;	else pin=0;

	switch (pin) {
		case 0:


//This checks if incomming signal is a 0 or a 1, depending on whether the length with the signal is held high
// or not
		pulseDuration = TAR;

		if((pulseDuration<maxLogic0Pulse) && (pulseDuration>minLogic0Pulse)){
				packet = (packet << 1) | 0;
		}
		if((pulseDuration<maxLogic1Pulse) && (pulseDuration>minLogic1Pulse)){
				packet = (packet << 1) | 1;
		}


			packetData[packetIndex++] = pulseDuration;
		TACTL = 0;					// kill the timer
		LOW_2_HIGH; 				// Sets up pin interrupt on positive edge
		break;

	case 1:
		TAR = 0x0000;
		TA0CCR0=0xFFFF;
		TACTL = ID_3 | TASSEL_2 | MC_1 | TAIE;	//this implements a counting system
												//each count should take about 8 times as long
		HIGH_2_LOW; 							// Sets up pin interrupt on positive edge
		break;
	}

	P2IFG &= ~BIT6;			// Clear the interrupt flag, for good luck

}



// -----------------------------------------------------------------------
//
// This interrupt is a way of reseting the reciever and packetIndex.
//
// -----------------------------------------------------------------------

#pragma vector = TIMER0_A1_VECTOR
__interrupt void timerOverflow (void) {

	TACTL = 0;
	TACTL &= ~TAIE;
	packetIndex = 0;  		//wait for next signal
	newIRPacket = TRUE; 	//decode signal
	TACTL &= ~TAIFG;  		//reset the flag
}
