#ifndef MANCHESTER_H_INCLUDED
#define MANCHESTER_H_INCLUDED

#include "typedefs.h"
#include "crc4.h"

#define MAN_0 (uint32)0x1
#define MAN_1 (uint32)0x2
#define STOPBIT (uint32)0x1

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
uint16 man_encode8(uint8 Di, uint8 bitConvertNum);

/// <summary>
/// Can encode up 16 databits to 32 Manchester bits.
/// </summary>
/// <param name="Di"></param>
/// <param name="bitConvertNum"></param>
/// <returns></returns>
uint32 man_encode16(uint16 Di, uint8 bitConvertNum);

/// <summary>
/// Can encode up 32 databits to 64 Manchester bits.
/// </summary>
/// <param name="Di"></param>
/// <param name="bitConvertNum"></param>
/// <returns></returns>
uint64 man_encode32(uint32 Di, uint8 bitConvertNum);

/// <summary>
/// Can decode up 16 Manchester bits to 8 data bits.
/// </summary>
/// <param name="Di"></param>
/// <param name="bitConvertNum"></param>
/// <returns></returns>
uint8 man_decode16(uint16 Di, uint8 bitConvertNum);

/// <summary>
/// Can decode up 32 Manchester bits to 16 data bits.
/// </summary>
/// <param name="Di"></param>
/// <param name="bitConvertNum"></param>
/// <returns></returns>
uint16 man_decode32(uint32 Di, uint8 bitConvertNum);

/// <summary>
/// Can decode up 64 Manchester bits to 32 data bits.
/// </summary>
/// <param name="Di"></param>
/// <param name="bitConvertNum"></param>
/// <returns></returns>
uint32 man_decode64(uint64 Di, uint8 bitConvertNum);

uint32 create_code(uint8 value);

#endif