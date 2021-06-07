#include "manchester.h"

uint16 man_encode8(uint8 Di, uint8 bitConvertNum)
{
	ASSERT(bitConvertNum < 9);
	uint32 Do = 0;
	uint8  Maske = 0x01;
	for (uint8 i = 0; i < bitConvertNum; i++)
	{
		if (Maske & Di)
		{
			Do |= (MAN_1 << (i << 1));
		}
		else
		{
			Do |= (MAN_0 << (i << 1));
		}
		Maske = Maske << 1;
	}
	return Do;
}

uint32 man_encode16(uint16 Di, uint8 bitConvertNum)
{
	ASSERT(bitConvertNum < 17);
	uint32 Do = 0;
	uint16  Maske = 0x01;
	for (uint8 i = 0; i < bitConvertNum; i++)
	{
		if (Maske & Di)
		{
			Do |= (MAN_1 << (i << 1));
		}
		else
		{
			Do |= (MAN_0 << (i << 1));
		}
		Maske = Maske << 1;
	}
	return Do;
}

uint64 man_encode32(uint32 Di, uint8 bitConvertNum)
{
	ASSERT(bitConvertNum < 33);
	uint64 Do = 0;
	uint32  Maske = 0x01;
	for (uint8 i = 0; i < bitConvertNum; i++)
	{
		if (Maske & Di)
		{
			Do |= ((uint64)MAN_1 << (i << 1));
		}
		else
		{
			Do |= ((uint64)MAN_0 << (i << 1));
		}
		Maske = Maske << 1;
	}
	return Do;
}

uint8 man_decode16(uint16 Di, uint8 bitConvertNum)
{
	ASSERT(bitConvertNum < 17);
	uint8 Do = 0;
	uint16 Maske = 0x3;
	for (uint8 i = 0; i < bitConvertNum; i+=2)
	{
		if (((Di & Maske) >> i) == MAN_1)
		{
			Do |= (1 << (i >> 1)); //1 mal nach rechts schieben ist wie durch 2 dividieren (i / 2)
		}
		Maske = Maske << 2;
	}
	return Do;
}

uint16 man_decode32(uint32 Di, uint8 bitConvertNum)
{
	ASSERT(bitConvertNum < 33);
	uint16 Do = 0;
	uint32 Maske = 0x3;
	for (uint8 i = 0; i < bitConvertNum; i+=2)
	{
		if (((Di & Maske) >> i) == MAN_1)
		{
			Do |= (1 << (i >> 1)); //1 mal nach rechts schieben ist wie durch 2 dividieren (i / 2)
		}
		Maske = Maske << 2;
	}
	return Do;
}

uint32 man_decode64(uint64 Di, uint8 bitConvertNum)
{
	ASSERT(bitConvertNum < 65);
	uint32 Do = 0;
	uint64 Maske = 0x3;
	for (uint8 i = 0; i < bitConvertNum; i+=2)
	{
		if (((Di & Maske) >> i) == MAN_1)
		{
			Do |= (1 << (i >> 1)); //1 mal nach rechts schieben ist wie durch 2 dividieren (i / 2)
		}
		Maske = Maske << 2;
	}
	return Do;
}

uint32 create_code(uint8 value)
{
	uint16 crcen_result = create_crc4(value);
	uint32 manen_result = man_encode16(crcen_result, 11);
	manen_result |= (STOPBIT << 22);
	manen_result <<= 1; //start bit
	return manen_result;
}