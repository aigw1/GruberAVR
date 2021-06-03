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
#include "crc4.h"
#include "typedefs.h"
#include "timerInterrupt.h"

volatile uint32 interruptSendeMaske = 0x1;
volatile uint32 interruptDatabits = 0;
volatile uint32 interruptReceivedData = 0;
volatile uint8  sentBitCounter = 0;
volatile uint8  receivedBitCounter = 0;

volatile bool   flag_caluclateNewValues = false;
volatile bool   flag_activeGapTime = false;

volatile uint32 manen_result;
/*Sende Interrupts*/
ISR(TIMER1_COMPA_vect)
{
	PORTB ^= (1 << PINB1);
	if(interruptDatabits & interruptSendeMaske)
	{
		PORTB |=  (1 << PINB0);
	}
	else
	{
		PORTB &= ~(1 << PINB0);
	}
	interruptSendeMaske <<= 1;
	sentBitCounter++;
	if(sentBitCounter > 24)
	{
		flag_caluclateNewValues = true;
		flag_activeGapTime = true;
		interruptDatabits = manen_result;
		interruptSendeMaske = 0x1;
		sentBitCounter = 0;
		TIMSK1 &= ~(1 << OCIE1A);
	}
	TCNT1 = 0;
}

ISR(TIMER1_COMPB_vect)
{
	PORTB &= ~(1 << PINB0);
	DDRB &= 0x00;
	stop_timer1();
}

/*Empfangs Interrupts*/
ISR(INT0_vect)
{
	TCNT3 = 0;
}

ISR(TIMER3_COMPA_vect)
{
	
}

ISR(TIMER3_COMPB_vect)
{
	if((PORTB & 0x1))
	{
		interruptReceivedData |= 0x8;
	}
	interruptReceivedData >>= 1;
	receivedBitCounter++;
	if(receivedBitCounter > 21)
	{
		receivedBitCounter = 0;
	}
}

ISR(TIMER3_COMPC_vect)
{
	if((PORTB & 0x1))
	{
		interruptReceivedData |= 0x8;
	}
	interruptReceivedData >>= 1;
	receivedBitCounter++;
	if(receivedBitCounter > 21)
	{
		receivedBitCounter = 0;
	}	
}

int main()
{
	sei();
	DDRB = 0xff;
	
	uint16 crcen_result = create_crc4(0x00);
	manen_result = man_encode16(crcen_result, 11);
	manen_result |= (STOPBIT << 22);
	interruptDatabits = manen_result;
	
	init_timer1(1270, 1270 * 8);
	start_timer1();
	while(true)
	{
		
	}
	return EXIT_SUCCESS;
}