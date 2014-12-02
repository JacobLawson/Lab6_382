#include <msp430.h>

#define move		500000
#define delay		1500000
#define halfturn	500000
#define fullturn	750000

void main(void)
{

WDTCTL = WDTPW|WDTHOLD;                 // stop the watchdog timer

    P1DIR &= ~BIT3;
    P1REN |= BIT3;

    // Left
    P2DIR |= BIT0;	// 1,2EN as OUT
    P2DIR |= BIT1;  // Sets direction of left motor
    P2DIR |= BIT2;							// P2.2 is associated with TA1CCR
    P2SEL |= BIT2;							// P2.2 is associated with TA1CCTL1

	// Right
   	P2DIR |= BIT5;  // 3,4EN as OUT
   	P2DIR |= BIT3;  //direction of right motor
   	P2DIR |= BIT4;							// P2.2 is associated with TA1CCR2
   	P2SEL |= BIT4;							// P2.2 is associated with TA1CCTL2

    TA1CTL = ID_3 | TASSEL_2 | MC_1;		// Use 1:8 presclar off MCLK
    TA1CCR0 = 0x0100;						// set signal period

    TA1CCR1 = 0x0020;
    TA1CCTL1 = OUTMOD_7;					// set TACCTL1 to Reset / Set mode

    TA1CCR2 = 0x0020;						// set TACCTL2 to Set / Reset mode
    TA1CCTL2 = OUTMOD_3;

    while (1)
    {
    	moveForward();
    	__delay_cycles(move);
    	stopMove();
    	__delay_cycles(delay);

    	rotateLeft();
    	__delay_cycles(halfturn);
    	stopMoving();
    	__delay_cycles(delay);

    	rotateRight();
    	__delay_cycles(halfturn);
    	stopMoving();
    	__delay_cycles(delay);

    	moveBackward();
    	__delay_cycles(move);
    	stopMoving();
    	__delay_cycles(delay);

    	rotateLeft();
    	__delay_cycles(fullturn);
    	stopMoving();
    	__delay_cycles(delay);

    	rotateRight();
    	__delay_cycles(fullturn);
    	stopMoving();
    	__delay_cycles(delay);

    }
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
