// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/asciistring8outofline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME7: QuotedPrintableToUnicodeString, retail 0x001062C0, zh_sweep
// packet 001062c0. The Zero Hour file is unchanged -- the whole gap was the
// AsciiString spelling. str() reads +0x08, so the data header is BFME's
// four-field one, and the by-value argument's destructor is a call rather
// than an inlined releaseBuffer, which is the asciistring8outofline shim.
//
// The packet's 374 bytes count the 25 int3 bytes of padding after the ret;
// the body is 349, which is what the ledger row already carried.
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: QuotedPrintable.cpp /////////////////////////////////////////////////////////
// Author: Matt Campbell, February 2002
// Description: Quoted-printable encode/decode
////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/QuotedPrintable.h"

// Retail's UnicodeString derives from StringBase<unsigned short> and holds
// nothing of its own, so its copy ctor is a forwarder retail inlines at every
// by-value-return and member-copy site: the bytes encode the base body at
// 0x00888400 (??0?$StringBase@G@@AAE@ABV0@@Z) directly. The vendored
// UnicodeString.h leaves the copy ctor declared and undefined, so without this
// cl emits an out-of-line call to ??0UnicodeString@@QAE@ABV0@@Z instead.
#include "string_base.h"

inline UnicodeString::UnicodeString(const UnicodeString &stringSrc)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
		*(const StringBase<unsigned short> *)&stringSrc);
}

#define MAGIC_CHAR '_'

// takes an integer and returns an ASCII representation
static char intToHexDigit(int num)
{
	if (num<0 || num >15) return '\0';
	if (num<10)
	{
		return '0' + num;
	}
	return 'A' + (num-10);
}

// convert an ASCII representation of a hex digit into the digit itself
static int hexDigitToInt(char c)
{
	if (c <= '9' && c >= '0') return (c - '0');
	if (c <= 'f' && c >= 'a') return (c - 'a' + 10);
	if (c <= 'F' && c >= 'A') return (c - 'A' + 10);
	return 0;
}

// Convert unicode strings into ascii quoted-printable strings
AsciiString UnicodeStringToQuotedPrintable(UnicodeString original)
{
	static char dest[1024];
	const char *src = (const char *)original.str();
	int i=0;
	while ( !(src[0]=='\0' && src[1]=='\0') && i<1021 )
	{
		if (!isalnum(*src))
		{
			dest[i++] = MAGIC_CHAR;
			dest[i++] = intToHexDigit((*src)>>4);
			dest[i++] = intToHexDigit((*src)&0xf);
		} else
		{
			dest[i++] = *src;
		}
		src ++;
		if (!isalnum(*src))
		{
			dest[i++] = MAGIC_CHAR;
			dest[i++] = intToHexDigit((*src)>>4);
			dest[i++] = intToHexDigit((*src)&0xf);
		}
		else
		{
			dest[i++] = *src;
		}
		src ++;
	}
	dest[i] = '\0';

	return dest;
}

// Convert ascii strings into ascii quoted-printable strings
AsciiString AsciiStringToQuotedPrintable(AsciiString original)
{
	static char dest[1024];
	const char *src = (const char *)original.str();
	int i=0;
	while ( src[0]!='\0' && i<1021 )
	{
		if (!isalnum(*src))
		{
			dest[i++] = MAGIC_CHAR;
			dest[i++] = intToHexDigit((*src)>>4);
			dest[i++] = intToHexDigit((*src)&0xf);
		} else
		{
			dest[i++] = *src;
		}
		src ++;
	}
	dest[i] = '\0';

	return dest;
}

// Convert ascii quoted-printable strings into unicode strings
UnicodeString QuotedPrintableToUnicodeString(AsciiString original)
{
	static unsigned short dest[1024];
	int i=0;

	unsigned char *c = (unsigned char *)dest;
	const unsigned char *src = (const unsigned char *)original.str();

	while (*src && i<1023)
	{
		if (*src == MAGIC_CHAR)
		{
			if (src[1] == '\0')
			{
				// string ends with MAGIC_CHAR
				break;
			}
			*c = hexDigitToInt(src[1]);
			src++;
			if (src[1] != '\0')
			{
				*c = *c<<4;
				*c = *c | hexDigitToInt(src[1]);
				src++;
			}
		}
		else
		{
			*c = *src;
		}
		src++;
		c++;
	}

	// Fixup odd-length strings
	if ((c-(unsigned char *)dest)%2)
	{
		// OK
	}
	else
	{
		*c = '\0';
		c++;
	}

	*c = 0;

	UnicodeString out(dest);
	return out;
}

// Convert ascii quoted-printable strings into ascii strings
AsciiString QuotedPrintableToAsciiString(AsciiString original)
{
	static unsigned char dest[1024];
	int i=0;

	unsigned char *c = (unsigned char *)dest;
	const unsigned char *src = (const unsigned char *)original.str();

	while (*src && i<1023)
	{
		if (*src == MAGIC_CHAR)
		{
			if (src[1] == '\0')
			{
				// string ends with MAGIC_CHAR
				break;
			}
			*c = hexDigitToInt(src[1]);
			src++;
			if (src[1] != '\0')
			{
				*c = *c<<4;
				*c = *c | hexDigitToInt(src[1]);
				src++;
			}
		}
		else
		{
			*c = *src;
		}
		src++;
		c++;
	}

	*c = 0;

	return AsciiString((const char *)dest);
}

