#ifndef INTERRUPT_H_INCLUDED
#define INTERRUPT_H_INCLUDED

#include <avr/interrupt.h>
#include "typedefs.h"

void enable_pinChange(uint8 pinChange);

void disable_pinChange(void);

#endif /* INTERRUPT_H_INCLUDED */