/*When PC is defined console outputs + assertions are enabled*/
/*When UC is defined console outputs + assertions are disabled*/
#define UC

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

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
volatile bool   flag_firstPinChange = false;

volatile bool   flag_sending = true;
volatile bool   flag_receiving = false;
volatile bool   flag_6BitDelay = true;
volatile bool   flag_vaildPinChange = false;

volatile uint32 manen_result;

/*Sende Interrupts*/
ISR(TIMER1_COMPA_vect)
{
	if (flag_activeGapTime)
	{
		flag_caluclateNewValues = true;
		sentBitCounter = 0;
		interruptDatabits = manen_result;
		interruptSendeMaske = 0x1;
	}
	if(flag_activeGapTime)
	{
		PORTB |= (1 << PINB0);
	}
	if(flag_sending && flag_6BitDelay && !flag_activeGapTime)
	{
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
			flag_activeGapTime = true;
		}
		TCNT1 = 0;
	}
}

/*Hand bus over to the other host*/
ISR(TIMER1_COMPB_vect)
{
	if(flag_sending && flag_6BitDelay && flag_activeGapTime)
	{
		PORTB &= ~(1 << PINB0);
		DDRB &= ~(1 << PINB0);
		if (!(PINB & (1 << PINB0))) //Pin low = no host connected
		{
			flag_activeGapTime = false;
			flag_sending = true;
			flag_receiving = false;
			DDRB |= 0xff;
		}
		else //Pin high = host connected
		{
			flag_activeGapTime = false;
			flag_receiving = true;
			flag_sending = false;
			flag_firstPinChange = true;
			flag_6BitDelay = false;
		}
		TCNT1 = 0;
	}
}

/*Delay to start the sending after 6 Bits*/
ISR(TIMER1_COMPC_vect)
{
	if(flag_sending && !flag_6BitDelay)
	{
		flag_6BitDelay = true;
		TCNT1 = 0;
	}
}

/*Empfangs Interrupts*/
ISR(PCINT0_vect)
{
	if(flag_receiving)
	{
		/*First pin Change = Start bit*/
		/*First sampled bit will be the start bit*/
		if (flag_firstPinChange && !(PINB & (1 << PINB0))) //Pin has to be low
		{
			flag_firstPinChange = false;
			flag_vaildPinChange = true;
		}
	}
	TCNT3 = 0;
}

//Takes over bus and gets ready for the sending interrupts
//Still has to be checked whether the connection in between is lost
ISR(TIMER3_COMPA_vect)
{
	if(flag_receiving && flag_vaildPinChange)
	{
		if (PINB & (1 << PINB0))
		{
			PORTB |= (1 << PINB0);	
			DDRB = 0xff;
			flag_vaildPinChange = false;
			flag_sending = true;
			flag_receiving = false;
			TCNT1 = 0;
		}
	}
	TCNT3 = 0;
}

ISR(TIMER3_COMPB_vect)
{
	if(flag_receiving && !flag_frameRecieved && flag_vaildPinChange)
	{		
		if((PINB & 0x1))
		{
			interruptReceivedData |= 0x1;
		}
		interruptReceivedData <<= 1;
		receivedBitCounter++;
		if(receivedBitCounter > 24)
		{
			receivedBitCounter = 0;
			flag_frameRecieved = true;
		}
	}
}

ISR(TIMER3_COMPC_vect)
{
	if(flag_receiving && !flag_frameRecieved && flag_vaildPinChange)
	{
		if((PINB & 0x1))
		{
			interruptReceivedData |= 0x1;
		}
		interruptReceivedData <<= 1;
		receivedBitCounter++;
		if(receivedBitCounter > 24)
		{
			receivedBitCounter = 0;
			flag_frameRecieved = true;
		}
	}
}

int main()
{
	CLKPR = 0x80;
	CLKPR = 0x00;
	
	sei();
	DDRB = 0xff;
	PORTB |= (1 << PINB0);
	manen_result = create_code(0x5E);
	interruptDatabits = manen_result;
	enable_pinChange(0);
	init_timer1(1270, 1270 * 8, 1270 * 5);
	init_timer3(1270 * 6, 635, 1905);
	start_timer1_interrupt();
	start_timer3_interrupt();
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