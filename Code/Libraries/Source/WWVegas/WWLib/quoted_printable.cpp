// cl: /DNDEBUG /MD /ICode/GameEngine/Include/Precompiled
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
#include "prerts.h"

// The retail WWLib StringBase header is four fields wide: its character data
// starts eight bytes after the object-owned data header.  Keep this TU-local
// ABI view so the conversion bodies inline the proven retail access.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
	void *m_data;
public:
	AsciiString();
	AsciiString(const char *);
	AsciiString(const AsciiString &);
	bool hasData() const { return m_data != 0; }
	const char *str() const
	{
		return m_data ? (const char *)((const char *)m_data + 8)
		              : (const char *)0x0107388B;
	}
	const char *data() const { return (const char *)((const char *)m_data + 8); }
	~AsciiString();
};

// WWLib's retail string header stores the data header at +0x00 and its UTF-16
// payload at +0x08.  This TU only needs that proven view for the encoder; the
// destructor remains the existing WWLib ABI call emitted by the compiler.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
	void *m_data;
public:
	UnicodeString();
	UnicodeString(const unsigned short *);
	UnicodeString(const UnicodeString &);
	const unsigned short *str() const
	{
		return m_data ? (const unsigned short *)((const char *)m_data + 8)
		              : (const unsigned short *)0x0107388C;
	}
	~UnicodeString();
};

#include "quoted_printable.h"

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
	static char *const dest = (char *)0x012ED8D8;
	const char *src = (const char *)original.str();
	int i=0;
	while ( !(src[0]=='\0' && src[1]=='\0') && i<1021 )
	{
		if (!isalnum(*src))
		{
			dest[i++] = MAGIC_CHAR;
			dest[i++] = intToHexDigit(((unsigned char)*src)>>4);
			dest[i++] = intToHexDigit(((unsigned char)*src)&0xf);
		} else
		{
			dest[i++] = *src;
		}
		src ++;
		if (!isalnum(*src))
		{
			dest[i++] = MAGIC_CHAR;
			dest[i++] = intToHexDigit(((unsigned char)*src)>>4);
			dest[i++] = intToHexDigit(((unsigned char)*src)&0xf);
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
	static char *const dest = (char *)0x012EDDA8;
	const char *src = (const char *)original.str();
	int i=0;
	while ( src[0]!='\0' && i<1021 )
	{
		if (!isalnum(*src))
		{
			dest[i++] = MAGIC_CHAR;
			dest[i++] = intToHexDigit(((unsigned char)*src)>>4);
			dest[i++] = intToHexDigit(((unsigned char)*src)&0xf);
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
// ?QuotedPrintableToUnicodeString present-unmatched
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
	static unsigned char *const dest = (unsigned char *)0x012EEC18;
	int i=0;

	unsigned char *c = (unsigned char *)dest;
	if (original.hasData())
	{
		const unsigned char *src = (const unsigned char *)original.data();

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
	}

	*c = 0;

	return AsciiString((const char *)dest);
}
