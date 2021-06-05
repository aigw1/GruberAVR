//TODO: Frameempfangen wurde noch nicht getestet

/*When PC is defined console outputs + assertions are enabled*/
/*When UC is defined console outputs + assertions are disabled*/
#define UC

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define F_CPU 2000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "binOutput.h"
#include "manchester.h"
#include "typedefs.h"
#include "timerInterrupt.h"
#include "interrupt.h"

volatile uint32 interruptSendeMaske = 0x1;
volatile uint32 interruptDatabits = 0;
volatile uint32 interruptReceivedData = 0;
volatile uint8  sentBitCounter = 0;
volatile uint8  receivedBitCounter = 0;

volatile bool   flag_caluclateNewValues = false;
volatile bool   flag_activeGapTime = false;
volatile bool   flag_frameRecieved = false;
volatile bool   flag_firstPinChange = true;

volatile uint32 manen_result;
/*Sende Interrupts*/
ISR(TIMER1_COMPA_vect)
{
	PORTB ^= (1 << PINB1);
	if((interruptDatabits & interruptSendeMaske) || flag_activeGapTime)
	{
		PORTB |=  (1 << PINB0);
	}
	else
	{
		PORTB &= ~(1 << PINB0);
	}
	interruptSendeMaske <<= 1;
	sentBitCounter++;
	if (flag_activeGapTime)
	{
		flag_caluclateNewValues = true;
		sentBitCounter = 0;
		interruptDatabits = manen_result;
		interruptSendeMaske = 0x1;
		TIMSK1 &= ~(1 << OCIE1A);
	}
	if(sentBitCounter > 24)
	{
		flag_activeGapTime = true;
	}
	TCNT1 = 0;
}

ISR(TIMER1_COMPB_vect)
{
	PORTB &= ~(1 << PINB0);
	DDRB &= 0x00;
	stop_timer1();	
	if (!(PINB & (1 << PINB0))) //Pin low = no host connected
	{
		start_timer1();
		flag_activeGapTime = false;
		DDRB |= 0xff;
	}
	else //Pin high = host connected
	{
		enable_pinChange(0);
		flag_firstPinChange = true;
	}
}

//Delay to start the sending after 6 Bits
ISR(TIMER1_COMPC_vect)
{
	
}

/*Empfangs Interrupts*/
// Wird PC-Int verwendet PINB0
ISR(PCINT0_vect)
{
	/*First pin Change = Start bit*/
	/*First sampled bit will be the start bit*/
	if (flag_firstPinChange && !(PINB & (1 << PINB0))) //Pin has to be low 
	{
		flag_firstPinChange = false;
		start_timer3();
	}
	TCNT3 = 0;
}

//Takes over bus and gets ready for the sending interrupts
//Still has to be checked whether the connection in between is lost
ISR(TIMER3_COMPA_vect)
{
	if (PINB & (1 << PINB0))
	{
		PORTB |= (1 << PINB0);
		DDRB = 0xff;
	}
}

ISR(TIMER3_COMPB_vect)
{
	if((PINB & 0x1))
	{
		interruptReceivedData |= 0x1;
	}
	interruptReceivedData <<= 1;
	receivedBitCounter++;
	if(receivedBitCounter > 24)
	{
		TIMSK3 &= ~(1 << OCIE1B);
		TIMSK3 &= ~(1 << OCIE1C);
		receivedBitCounter = 0;
		flag_frameRecieved = true;
	}
}

ISR(TIMER3_COMPC_vect)
{
	if((PINB & 0x1))
	{
		interruptReceivedData |= 0x1;
	}
	interruptReceivedData <<= 1;
	receivedBitCounter++;
	if(receivedBitCounter > 24)
	{
		TIMSK3 &= ~(1 << OCIE1B);
		TIMSK3 &= ~(1 << OCIE1C);
		receivedBitCounter = 0;
		flag_frameRecieved = true;
	}
}

int main()
{
	sei();
	DDRB = 0xff;
	manen_result = create_code(0x5E);
	interruptDatabits = manen_result;
	init_timer1(1270, 1270 * 8, 1270 * 6);
	init_timer3(1270 * 6, 635, 1905);	//1270/2=635, 635+1270=1905
	start_timer1();
	while(true)
	{
		if(flag_caluclateNewValues)
		{
			flag_caluclateNewValues = false;
		}
		if(flag_frameRecieved)
		{
			flag_frameRecieved = false;
		}
	}
	return EXIT_SUCCESS;
}