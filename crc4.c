#include "crc4.h"

uint16 create_crc4(uint8 num)
{
	uint8 shifting_table[] = { 0x3, 0x2, 0x1, 0x0 };
	uint16 result = 0;
	uint8 rest = ((num & 0xF0) >> 4);
	for (uint8 i = 0; i < 5; i++)
	{
		if (rest & 0x8)
		rest ^= CRC4_POLYNOM;
		if (i <= 3)
		{
			rest <<= 1;
			rest |= ((num & (0x1 << shifting_table[i])) >> shifting_table[i]);
		}
	}
	result = (num << 3);
	result |= rest;
	return result;
}

uint8 strip_crc4(uint16 num)
{
	return (uint8)(num >> 3);
}

bool  check_crc4(uint16 num)
{
	uint8 shifting_table[] = { 0x3, 0x2, 0x1, 0x0 };
	uint8 data_bit = strip_crc4(num);
	uint8 rest = (data_bit & (0xF << 4) >> 4);
	for (uint8 i = 0; i < 5; i++)
	{
		if (rest & 0x8)
		rest ^= CRC4_POLYNOM;
		if (i <= 3)
		{
			rest <<= 1;
			rest |= ((data_bit & (0x1 << shifting_table[i])) >> shifting_table[i]);
		}
	}
	if (rest == (num & 0x7))
	return true;
	return false;
}