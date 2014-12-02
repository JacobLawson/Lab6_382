//-----------------------------------------------------------------
// Name:	Coulston
// File:	lab5.h
// Date:	Fall 2014
// Purp:	Include file for the MSP430
//-----------------------------------------------------------------


typedef		unsigned char		int8;
typedef		unsigned short		int16;
typedef		unsigned long		int32;
typedef		unsigned long long	int64;

#define		TRUE				1
#define		FALSE				0


void initMSP430();
__interrupt void pinChange (void);
__interrupt void timerOverflow (void);

#define		IR_PIN			(P2IN & BIT6)
#define		HIGH_2_LOW		P2IES |= BIT6
#define		LOW_2_HIGH		P2IES &= ~BIT6


#define		averageLogic0Pulse	0x0200
#define		averageLogic1Pulse	0x0645
#define		averageStartPulse	0x1100
#define		minLogic0Pulse		averageLogic0Pulse - 100
#define		maxLogic0Pulse		averageLogic0Pulse + 100
#define		minLogic1Pulse		averageLogic1Pulse - 100
#define		maxLogic1Pulse		averageLogic1Pulse + 100
#define		minStartPulse		averageStartPulse - 100
#define		maxStartPulse		averageStartPulse + 100

#define		PWR		0x20DF10EF
#define		ZERO	0x20DF08F7
#define		ONE		0x20DF8877
#define		TWO		0x20DF48B7
#define		THR		0x20DFC837

#define		VOL_UP	0x20DF40BF
#define		VOL_DW	0x20DFC03F
#define		CH_UP	0x20DF00FF
#define		CH_DW	0x20DF807F
