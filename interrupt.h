#ifndef INTERRUPT_H_INCLUDED
#define INTERRUPT_H_INCLUDED

void enable_pinChange(uint8 pinChange)
{
	PCMSK0 |= (1 << (PCINT0 + pinChange));
	PCICR  |= (1 << PCIE0);
}

void disable_pinChange()
{
	PCMSK0 &= ~(1 << PCINT0);
	PCICR  &= ~(1 << PCIE0);
}

#endif /* INTERRUPT_H_INCLUDED */