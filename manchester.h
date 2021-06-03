#ifndef MANCHESTER_H_INCLUDED
#define MANCHESTER_H_INCLUDED

#include "typedefs.h"

#define MAN_0 (uint32)0x2
#define MAN_1 (uint32)0x1
#define STOPBIT (uint32) 0x5

#ifndef UC
#include <assert.h>
#define ASSERT(x) assert(x)
#else
#define ASSERT(x)
#endif // !UC

/// <summary>
/// Can encode up 8 databits to 16 Manchester bits.
/// </summary>
/// <param name="Di"></param>
/// <param name="bitConvertNum"></param>
/// <returns></returns>
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
/// <summary>
/// Can encode up 16 databits to 32 Manchester bits.
/// </summary>
/// <param name="Di"></param>
/// <param name="bitConvertNum"></param>
/// <returns></returns>
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
/// <summary>
/// Can encode up 32 databits to 64 Manchester bits.
/// </summary>
/// <param name="Di"></param>
/// <param name="bitConvertNum"></param>
/// <returns></returns>
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

/// <summary>
/// Can decode up 16 Manchester bits to 8 data bits.
/// </summary>
/// <param name="Di"></param>
/// <param name="bitConvertNum"></param>
/// <returns></returns>
uint8 man_decode16(uint16 Di, uint8 bitConvertNum)
{
	ASSERT(bitConvertNum < 17);
	uint8 Do = 0;
	uint16 Maske = 0x3;
	for (uint8 i = 0; i < bitConvertNum; i+=2)
	{
		if (((Di & Maske) >> i) == MAN_1)
		{
			Do |= (1 << (i >> 1)); //1 mal nach rechts schieben ist wei durch 2 dividieren (i / 2)
		}
		Maske = Maske << 2;
	}
	return Do;
}
/// <summary>
/// Can decode up 32 Manchester bits to 16 data bits.
/// </summary>
/// <param name="Di"></param>
/// <param name="bitConvertNum"></param>
/// <returns></returns>
uint16 man_decode32(uint32 Di, uint8 bitConvertNum)
{
	ASSERT(bitConvertNum < 33);
	uint16 Do = 0;
	uint32 Maske = 0x3;
	for (uint8 i = 0; i < bitConvertNum; i+=2)
	{
		if (((Di & Maske) >> i) == MAN_1)
		{
			Do |= (1 << (i >> 1)); //1 mal nach rechts schieben ist wei durch 2 dividieren (i / 2)
		}
		Maske = Maske << 2;
	}
	return Do;
}
/// <summary>
/// Can decode up 64 Manchester bits to 32 data bits.
/// </summary>
/// <param name="Di"></param>
/// <param name="bitConvertNum"></param>
/// <returns></returns>
uint32 man_decode64(uint64 Di, uint8 bitConvertNum)
{
	ASSERT(bitConvertNum < 65);
	uint32 Do = 0;
	uint64 Maske = 0x3;
	for (uint8 i = 0; i < bitConvertNum; i+=2)
	{
		if (((Di & Maske) >> i) == MAN_1)
		{
			Do |= (1 << (i >> 1)); //1 mal nach rechts schieben ist wei durch 2 dividieren (i / 2)
		}
		Maske = Maske << 2;
	}
	return Do;
}

#endif