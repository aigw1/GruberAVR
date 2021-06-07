#include "interrupt.h"

void enable_pinChange(uint8 pinChange)
{
	PCMSK0 |= (1 << (PCINT0 + pinChange));
	PCICR  |= (1 << PCIE0);
}

void disable_pinChange(void)
{
	PCMSK0 &= ~(1 << PCINT0);
	PCICR  &= ~(1 << PCIE0);
}