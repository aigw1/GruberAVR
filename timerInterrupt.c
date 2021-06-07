#include "timerInterrupt.h"

void init_timer1(uint16 OCRA, uint16 OCRB, uint16 OCRC)
{
	/*Timer mode: Normal*/
	TCCR1A &= ~(1 << WGM10);
	TCCR1A &= ~(1 << WGM11);
	TCCR1B &= ~(1 << WGM12);
	TCCR1B &= ~(1 << WGM13);
	
	/*Prescaler 1:1*/
	#ifndef DEBUG
	TCCR1B |=  (1 << CS10);
	TCCR1B &= ~(1 << CS11);
	TCCR1B &= ~(1 << CS12);
	#endif
	
	/*Compare value*/
	OCR1A = OCRA;
	OCR1B = OCRB;
	OCR1C = OCRC;
	
	/*Debug Prescaler 1:1024*/
	#ifdef DEBUG
	TCCR1B |=  (1 << CS10);
	TCCR1B &= ~(1 << CS11);
	TCCR1B |=  (1 << CS12);
	#endif
}

void init_timer3(uint16 OCRA, uint16 OCRB, uint16 OCRC)
{
	/*Timer mode: Normal*/
	TCCR3A &= ~(1 << WGM30);
	TCCR3A &= ~(1 << WGM31);
	TCCR3B &= ~(1 << WGM32);
	TCCR3B &= ~(1 << WGM33);
	
	/*Prescaler 1:1*/
	#ifndef DEBUG
	TCCR3B |=  (1 << CS30);
	TCCR3B &= ~(1 << CS31);
	TCCR3B &= ~(1 << CS32);
	#endif
	
	/*Compare value*/
	OCR3A = OCRA;
	OCR3B = OCRB;
	OCR3C = OCRC;
	
	/*Debug Prescaler 1:1024*/
	#ifdef DEBUG
	TCCR3B |=  (1 << CS30);
	TCCR3B &= ~(1 << CS31);
	TCCR3B |=  (1 << CS32);
	#endif
}

void start_timer1(void)
{
	TCNT1 = 0;
	#ifndef DEBUG
	TCCR1B |=  (1 << CS10);
	TCCR1B &= ~(1 << CS11);
	TCCR1B &= ~(1 << CS12);
	#else
	TCCR1B |=  (1 << CS10);
	TCCR1B &= ~(1 << CS11);
	TCCR1B |=  (1 << CS12);
	#endif
	TIMSK1 |= (1 << OCIE1A);
	TIMSK1 |= (1 << OCIE1B);
	TIMSK1 |= (1 << OCIE1C);
}

void start_timer3(void)
{
	TCNT3 = 0;
	#ifndef DEBUG
	TCCR3B |=  (1 << CS30);
	TCCR3B &= ~(1 << CS31);
	TCCR3B &= ~(1 << CS32);
	#else
	TCCR3B |=  (1 << CS30);
	TCCR3B &= ~(1 << CS31);
	TCCR3B |=  (1 << CS32);
	#endif
	TIMSK3 |=  (1 << OCIE3A);
	TIMSK3 |=  (1 << OCIE3B);
	TIMSK3 |=  (1 << OCIE3C);
}

void stop_timer1(void)
{

	TCCR1B &= ~(1 << CS10);
	TCCR1B &= ~(1 << CS11);
	TCCR1B &= ~(1 << CS12);
	TIMSK1 &= ~(1 << OCIE1A);
	TIMSK1 &= ~(1 << OCIE1B);
	TIMSK1 &= ~(1 << OCIE1C);
	TCNT1 = 0;
}

void stop_timer3(void)
{
	TCCR3B &= ~(1 << CS30);
	TCCR3B &= ~(1 << CS31);
	TCCR3B &= ~(1 << CS32);
	TIMSK3 &= ~(1 << OCIE3A);
	TIMSK3 &= ~(1 << OCIE3B);
	TIMSK3 &= ~(1 << OCIE3C);
	TCNT3 = 0;
}