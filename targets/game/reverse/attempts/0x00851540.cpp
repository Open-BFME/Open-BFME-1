// ?getNextQuotedAsciiString@INI@@QAE?AVAsciiString@@XZ
// partial score=0.65 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
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
//
//  (c) 2001-2003 Electronic Arts Inc.
//
////////////////////////////////////////////////////////////////////////////////

// Donor: Code/GameEngine/Source/Common/INI/INI_stl.cpp, duplicated in
// Code/GameEngine/Source/Common/INI/ini_parsers.cpp.  The donor body is the
// canonical BFME INI quoted-token implementation; this TU owns its retail
// 0x00851540 body.
#include <stddef.h>
#include <string.h>
#include "Common/INIException.h"

enum { INI_MAX_CHARS_PER_LINE = 1028 };

// TU-local extension of reference/shims/stringinline/StringInline.h.  The
// inline special members are the proven BFME by-value ABI; the two-argument
// setter is declared on the base because retail computes the source length
// inline before writing the returned string.
template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

public:
	void set(const T *text, int len);

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	void set(const char *text) { StringBase<char>::set(text); }
};

class INI
{
public:
	AsciiString getNextQuotedAsciiString();

	const char *getNextTokenOrNull(const char *seps = NULL)
	{
		if (seps == NULL)
			seps = m_seps;
		return strtok(NULL, seps);
	}

	const char *getNextToken(const char *seps = NULL)
	{
		if (seps == NULL)
			seps = m_seps;
		const char *token = strtok(NULL, seps);
		if (token == NULL)
			throw INIException(3, "Expected additional data after '%s'", seps);
		return token;
	}

	const char *getSepsQuote()
	{
		return m_sepsQuote;
	}

private:
	char m_prefix[0x414];
	const char *m_seps;
	const char *m_sepsPercent;
	const char *m_sepsColon;
	const char *m_sepsQuote;
};

// ?getNextQuotedAsciiString@INI@@QAE?AVAsciiString@@XZ
AsciiString INI::getNextQuotedAsciiString()
{
	AsciiString result;
	char buff[INI_MAX_CHARS_PER_LINE];

	const char *token = getNextTokenOrNull();	// if null, just leave an empty string
	if (token != NULL)
	{
		if (token[0] != '\"')
		{
			// if token is simply "
			((StringBase<char> *)&result)->set( token, strlen(token) );	// Start following the "
		}
		else
		{
			int strLen = 0;
			bool done = false;
			if ((strLen = strlen(token)) > 1)
			{
				strcpy(buff, &token[1]);	//skip the starting quote
				//Check for end of quoted string.  Checking here fixes cases where quoted string on same line with other data.
				if (buff[strLen - 2] == '"')	//skip ending quote if present
				{
					buff[strLen - 2] = '\0';
					done = true;
				}
			}

			if (!done)
			{
				token = getNextToken(getSepsQuote());

				if (strlen(token) > 1 && token[1] != '\t')
				{
					strcat(buff, " ");
					strcat(buff, token);
				}
				else
				{
					int buflen = strlen(buff);
					if (buff[buflen - 1] == '\"')
						buff[buflen - 1] = '\0';
				}
			}
			((StringBase<char> *)&result)->set(buff, strlen(buff));
		}
	}
	return result;
}
