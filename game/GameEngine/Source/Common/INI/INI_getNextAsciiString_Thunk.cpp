// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ob1 /Iinputs/reference/shims/ini_inline /Iinputs/reference/shims/ini /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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
//	(c) 2001-2003 Electronic Arts Inc.															//
////////////////////////////////////////////////////////////////////////////////

// Readable body recovered from the canonical donor:
// game/GameEngine/Source/Common/INI/INI_stl.cpp
// The donor retains the retail regular getNextAsciiString behavior, including
// its static token buffer and null-token path.  This source owns the real C++
// definition for the ledger row at 0x008516E0.
#include "PreRTS.h"
#include "Common/INI.h"

// ?getNextAsciiString@INI@@QAE?AVAsciiString@@XZ
AsciiString INI::getNextAsciiString()
{
	AsciiString result;

	const char *token = getNextTokenOrNull();	// if null, just leave an empty string
	if (token != NULL)
	{
		if (token[0] != '"')
		{
			// Retail keeps this arm's length calculation in the caller and calls
			// StringBase::set(const char *, int) directly at 0x00887D20.
			StringBase<char> *base = (StringBase<char> *)&result;
			base->set( token, strlen(token) );
		}
		else
		{
			static char buff[INI_MAX_CHARS_PER_LINE];
			buff[0] = 0;
			if (strlen(token) > 1)
			{
				strcpy(buff, &token[1]);
			}

			token = getNextTokenOrNull(getSepsQuote());
			if (token)
			{
				if (strlen(token) > 1 && token[1] != '\t')
				{
					strcat(buff, " ");
				}
				strcat(buff, token);
				result.set(buff);
			}
			else
			{
				Int len = strlen(buff);
				if (len && buff[len-1] == '"')
				{
					buff[len-1] = 0;
				}
				result.set(buff);
			}
		}
	}
	return result;
}
