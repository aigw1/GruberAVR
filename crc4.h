#ifndef CRC4_H_INCLUDED
#define CRC4_H_INCLUDED

#include "typedefs.h"

#define CRC4_POLYNOM (uint32)0xB

/// <summary>
/// Creates crc4 for 8-bits.
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
uint16 create_crc4(uint8 num);

/// <summary>
/// Stips the last 3 Parity bits of the crc4.
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
uint8 strip_crc4(uint16 num);

/// <summary>
/// Checks incoming data whether the parity and data bits are right.
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
bool  check_crc4(uint16 num);

#endif