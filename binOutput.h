#ifndef UC
#ifndef BINOUTPUT_H_INCLUDED
#define BINOUTPUT_H_INCLUDED
#include <stdio.h>
#include "typedefs.h"

void bin_output8(uint8 num)
{
	printf("\n");
	for (uint8 i = 0; i < 8; i++)
	{
		if (num & (0x80 >> i))
		{
			printf("1");
			continue;
		}
		printf("0");
	}
	return;
}
void bin_output16(uint16 num)
{
	printf("\n");
	for (uint8 i = 0; i < 16; i++)
	{
		if (num & (0x8000 >> i))
		{
			printf("1");
			continue;
		}
		printf("0");
	}
	return;
}
void bin_output32(uint32 num)
{
	printf("\n");
	for (uint8 i = 0; i < 32; i++)
	{
		if (num & (0x80000000 >> i))
		{
			printf("1");
			continue;
		}
		printf("0");
	}
	return;
}
void bin_output64(uint64 num)
{
	printf("\n");
	for (uint8 i = 0; i < 64; i++)
	{
		if (num & (0x8000000000000000 >> i))
		{
			printf("1");
			continue;
		}
		printf("0");
	}
	return;
}

#endif // !BINOUTPUT_H_INCLUDED
#endif // !UC