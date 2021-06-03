/*
 * timerInterrupt.h
 *
 * Created: 23.04.2021 09:48:02
 *  Author: wolfg
 */ 


#ifndef TIMERINTERRUPT_H_INCLUDED
#define TIMERINTERRUPT_H_INCLUDED

void init_timer1(uint16 OCRA, uint16 OCRB)
{
	/*Timer mode: Normal*/
	TCCR1A &= ~(1 << WGM10);
	TCCR1A &= ~(1 << WGM11);
	TCCR1B &= ~(1 << WGM12);
	TCCR1B &= ~(1 << WGM13);
	
	/*Prescaler 1:1*/
	//TCCR1B |=  (1 << CS10);
	//TCCR1B &= ~(1 << CS11);
	//TCCR1B &= ~(1 << CS12);
	
	/*Compare value*/
	OCR1A = OCRA;
	OCR1B = OCRB;
	
	/*Debug Prescaler 1:1024*/
	TCCR1B |=  (1 << CS10);
	TCCR1B &= ~(1 << CS11);
	TCCR1B |=  (1 << CS12);
}

void init_timer3(uint16 OCRA, uint16 OCRB, uint16 OCRC)
{
	/*Timer mode: Normal*/
	TCCR3A &= ~(1 << WGM30);
	TCCR3A &= ~(1 << WGM31);
	TCCR3B &= ~(1 << WGM32);
	TCCR3B &= ~(1 << WGM33);
	
	/*Prescaler 1:1*/
	//TCCR3B |=  (1 << CS30);
	//TCCR3B &= ~(1 << CS31);
	//TCCR3B &= ~(1 << CS32);
	
	/*Compare value*/
	OCR3A = OCRA;
	OCR3B = OCRB;
	OCR3C = OCRC;
	
	/*Debug Prescaler 1:1024*/
	TCCR3B |=  (1 << CS30);
	TCCR3B &= ~(1 << CS31);
	TCCR3B |=  (1 << CS32);
}

void start_timer1()
{
	TCNT1 = 0;
	TCCR1B |=  (1 << CS10);
	TCCR1B &= ~(1 << CS11);
	TCCR1B &= ~(1 << CS12);
	TIMSK1 |= (1 << OCIE1A);
	TIMSK1 |= (1 << OCIE1B);
}

void start_timer3()
{
	TCNT3 = 0;
	TCCR3B |=  (1 << CS30);
	TCCR3B &= ~(1 << CS31);
	TCCR3B &= ~(1 << CS32);
	TIMSK3 |=  (1 << OCIE3A);
	TIMSK3 |=  (1 << OCIE3B);
}

void stop_timer1()
{
	TCCR1B &= ~(1 << CS10);
	TCCR1B &= ~(1 << CS11);
	TCCR1B &= ~(1 << CS12);
	TIMSK1 &= ~(1 << OCIE1A);
}

void stop_timer3()
{
	TCCR3B &= ~(1 << CS30);
	TCCR3B &= ~(1 << CS31);
	TCCR3B &= ~(1 << CS32);
	TIMSK3 &= ~(1 << OCIE3A);
}

#endif /* TIMERINTERRUPT_H_INCLUDED */