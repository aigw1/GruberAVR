#ifndef TIMERINTERRUPT_H_INCLUDED
#define TIMERINTERRUPT_H_INCLUDED

#include <avr/interrupt.h>
#include "typedefs.h"

void init_timer1(uint16 OCRA, uint16 OCRB, uint16 OCRC);
void init_timer3(uint16 OCRA, uint16 OCRB, uint16 OCRC);

void start_timer1(void);
void start_timer3(void);
void start_timer1_interrupt(void);
void start_timer3_interrupt(void);

void stop_timer1(void);
void stop_timer3(void);
void stop_timer1_interrupt(void);
void stop_timer3_interrupt(void);

#endif /* TIMERINTERRUPT_H_INCLUDED */